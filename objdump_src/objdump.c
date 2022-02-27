/*
** EPITECH PROJECT, 2021
** nm
** File description:
** objdump
*/

#include "objdump.h"

void print_readable(char *content, elf_t *elf, int i, int j)
{
    for (int k = 0; k < 16; k++) {
        if (k < elf->shdr[i].sh_offset + elf->shdr[i].sh_size - j) {
            if (content[k] > 31 && content[k] < 127)
                putchar(content[k]);
            else
                putchar('.');
        }
        else
            printf(" ");
    }
}

void print_hexad(unsigned char *content, elf_t *elf, int i, int j)
{
    for (int k = 0; k < 16; k += 1) {
        if (k < elf->shdr[i].sh_offset + elf->shdr[i].sh_size - j)
            printf("%02x", content[k]);
        else
            printf("  ");
        if (!((k + 1) % 4))
            printf(" ");
    }
    printf(" ");
}

void print_section(elf_t *elf)
{
    unsigned char *data = NULL;

    for (int i = 0; i < elf->ehdr->e_shnum; i += 1) {
        if (elf->shdr[i].sh_type == SHT_SYMTAB || strcmp(elf->strtab + \
        elf->shdr[i].sh_name, ".strtab") == 0 || strcmp(elf->strtab + \
        elf->shdr[i].sh_name, ".shstrtab") == 0 || elf->shdr[i].sh_type \
        == SHT_SYMTAB_SHNDX || elf->shdr[i].sh_type == SHT_NOBITS || \
        elf->shdr[i].sh_size == 0)
            continue;
        printf("\nContents of section %s:", elf->strtab + elf->shdr[i].sh_name);
        Elf64_Off offset = elf->shdr[i].sh_offset;
        Elf64_Off size = elf->shdr[i].sh_size;
        for (int j = offset; j < offset + size; j += 16) {
            data = (unsigned char *) elf->ehdr + j;
            printf("\n %04x ", (int)elf->shdr[i].sh_addr + j - \
            elf->shdr[i].sh_offset);
            print_hexad(data, elf, i, j);
            print_readable(data, elf, i, j);
        }
    }
}

void objdump(int fd, struct stat sb, char *filename)
{
    elf_t *elf = malloc(sizeof(elf_t));

    elf->data = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (elf->data == NULL)
        exit (84);
    if (!check_magic(elf->data)) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", filename);
        exit(84);
    }
    elf->ehdr = (Elf64_Ehdr *) elf->data;
    elf->shdr = (Elf64_Shdr *) (elf->data + elf->ehdr->e_shoff);
    elf->strtab = (char *)elf->ehdr + \
    elf->shdr[elf->ehdr->e_shstrndx].sh_offset;
    print_header(elf, filename);
    print_section(elf);
}

int main(int ac, char **av)
{
    int fd = 0;
    struct stat sb;

    if ((fd = open(av[1], O_RDONLY)) == -1) {
        fprintf(stderr, "objdump: \'%s\': No such file\n", av[1]);
        exit(84);
    }
    fstat(fd, &sb);
    objdump(fd, sb, av[1]);
    puts("\0");
    close(fd);
    return 0;
}