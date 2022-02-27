/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-mehdi.mourjane
** File description:
** stack
*/

#include "nm.h"

elf_t *get_sym_strtab(elf_t *elf)
{
    for (int i = 0; i < elf->ehdr->e_shnum; i++)
        if (elf->shdr[i].sh_type == SHT_SYMTAB) {
            elf->sym = (Elf64_Sym *)((void *)elf->ehdr + \
            elf->shdr[i].sh_offset);
            elf->sym_end = (Elf64_Sym *)((void *) elf->sym +\
            elf->shdr[i].sh_size);
            elf->strtab = (char *)elf->ehdr + \
            elf->shdr[elf->shdr[i].sh_link].sh_offset;
        }
    return elf;
}

nm_list_t **get_section(elf_t *elf)
{
    nm_list_t **nm_list = malloc(sizeof(nm_list_t) * elf->ehdr->e_shnum);
    int j = 0;

    for (Elf64_Sym *tmp = elf->sym; tmp < elf->sym_end; tmp++)
        if (tmp->st_info != STT_SECTION && tmp->st_info != STT_FILE) {
            nm_list[j] = malloc(sizeof(nm_list_t));
            nm_list[j]->sym = tmp;
            nm_list[j]->name = (char *)&elf->strtab[tmp->st_name];
            nm_list[j]->value = tmp->st_value;
            nm_list[j]->type = set_type(tmp, elf->shdr);
            j++;
        }
    nm_list[j] = NULL;
    return nm_list;
}

nm_list_t **sort_nm(nm_list_t **nm_list, int size)
{
    nm_list_t *tmp;
    for (int j = 0; j <= size * 2 - 1; j++)
        for (int i = 0; nm_list[i + 1]; i++) {
            if (strcmp(nm_list[i]->name_cook, nm_list[i + 1]->name_cook) > 0) {
                tmp = nm_list[i];
                nm_list[i] = nm_list[i + 1];
                nm_list[i + 1] = tmp;
            }
            if (strcmp(nm_list[i]->name_cook, nm_list[i + 1]->name_cook) == 0)
                if (nm_list[i + 1]->name[0] == '_' && \
                nm_list[i]->name[0] != '_') {
                    tmp = nm_list[i];
                nm_list[i] = nm_list[i + 1];
                nm_list[i + 1] = tmp;
                }
        }
    return nm_list;
}

void nm(int fd, struct stat sb, char *filename)
{
    elf_t *elf = malloc(sizeof(elf_t));
    nm_list_t **nm_list = NULL;

    elf->data = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (!check_magic(elf->data)) {
        fprintf(stderr, "nm: %s: file format not recognized\n", filename);
        exit(84);
    }
    elf->ehdr = (Elf64_Ehdr *) elf->data;
    elf->shdr = (Elf64_Shdr *) (elf->data + elf->ehdr->e_shoff);
    elf = get_sym_strtab(elf);
    nm_list = get_section(elf);
    nm_list = cook_name(nm_list);
    nm_list = sort_nm(nm_list, elf->ehdr->e_shnum);
    print_nm(nm_list);
}

int main(int ac, char **av)
{
    char *data = NULL;
    int fd = 0;
    struct stat sb;

    if (av[1] == NULL)
        av[1] = "a.out";
    if ((fd = open(av[1], O_RDONLY)) == -1) {
        fprintf(stderr, "nm: \'%s\': No such file\n", av[1]);
        exit(84);
    }
    fstat(fd, &sb);
    nm(fd, sb, av[1]);
    close(fd);
    return 0;
}