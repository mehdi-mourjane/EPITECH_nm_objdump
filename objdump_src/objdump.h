/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-mehdi.mourjane
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <unistd.h>
#include <stdio.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct elf_s elf_t;
struct elf_s {
    char *data;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    char *strtab;
};

void print_header(elf_t *elf, char *filename);
int check_magic(char *data);

#endif /* !OBJDUMP_H_ */
