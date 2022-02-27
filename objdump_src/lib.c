/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-mehdi.mourjane
** File description:
** lib
*/

#include "objdump.h"

void print_header(elf_t *elf, char *filename)
{
    printf("\n%s:     %s %s\nstart address 0x%016x\n",
    filename, "file format elf64-x86-64\narchitecture: i386:x86-64,",\
    "flags 0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED" , elf->ehdr->e_entry);
}

int check_magic(char *data)
{
    if (data && data[0] == 127 && strncmp(&data[1], "ELF", 3) == 0)
        return 1;
    return 0;
}