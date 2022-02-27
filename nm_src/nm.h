/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-mehdi.mourjane
** File description:
** nm
*/

#ifndef __MY_NM
#define __MY_NM

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct elf_s elf_t;
struct elf_s {
        char *data;
        Elf64_Ehdr *ehdr;
        Elf64_Shdr *shdr;
        Elf64_Sym *sym;
        Elf64_Sym *sym_end;
        char *strtab;
};

typedef struct nm_list_s nm_list_t;
struct nm_list_s {
        char *name;
        char *name_cook;
        int value;
        char type;
        Elf64_Sym *sym;
};

typedef struct s_flags
{
    int stt;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    char type;
} t_flags;

static t_flags                localflags[] = {
    { STT_NOTYPE, SHT_PROGBITS, 0, 'n' },
    { STT_NOTYPE, SHT_PROGBITS, 2, 'r' },
    { STT_NOTYPE, SHT_PROGBITS, 50, 'r' },
    { STT_NOTYPE, SHT_PROGBITS, 3, 'd' },
    { STT_NOTYPE, SHT_PROGBITS, 6, 't' },
    { STT_NOTYPE, SHT_NOBITS, 3, 'b' },
    { STT_OBJECT, SHT_DYNAMIC, 3, 'd' },
    { STT_OBJECT, SHT_NOTE, 2, 'r' },
    { STT_OBJECT, SHT_FINI_ARRAY, 3, 't' },
    { STT_OBJECT, SHT_INIT_ARRAY, 3, 't' },
    { STT_OBJECT, SHT_PROGBITS, 0, 'n' },
    { STT_OBJECT, SHT_PROGBITS, 2, 'r' },
    { STT_OBJECT, SHT_PROGBITS, 50, 'r' },
    { STT_OBJECT, SHT_PROGBITS, 3, 'd' },
    { STT_OBJECT, SHT_NOBITS, 3, 'b' },
    { STT_FUNC, SHT_PROGBITS, 6, 't' },
    { STT_TLS, SHT_PROGBITS, 1027, 'd' },
    { STT_TLS, SHT_NOBITS, 1027, 'b' },
    { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

static t_flags                globflags[] = {
    { STT_NOTYPE, SHT_PROGBITS, 3, 'D' },
    { STT_OBJECT, SHT_PROGBITS, 3, 'D' },
    { STT_OBJECT, SHT_PROGBITS, 2, 'R' },
    { STT_OBJECT, SHT_NOBITS, 3, 'B' },
    { STT_FUNC, SHT_NULL, 0, 'U' },
    { STT_FUNC, SHT_PROGBITS, 6, 'T' },
    { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

char global_symbol64(Elf64_Sym *symtab, Elf64_Shdr *shdr);
char local_symbol64(Elf64_Sym *symtab, Elf64_Shdr *shdr);
char c_flag(Elf64_Sym *symtab);
char weak_symbol64(Elf64_Sym *symtab);
char set_type(Elf64_Sym *sym, Elf64_Shdr *shdr);

char *my_strcpy(char *str);
nm_list_t **cook_name(nm_list_t **nm_list);
nm_list_t **print_nm(nm_list_t **nm_list);
int check_magic(char *data);

#endif