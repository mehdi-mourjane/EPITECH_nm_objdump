/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-mehdi.mourjane
** File description:
** symbol
*/

#include "nm.h"

char global_symbol64(Elf64_Sym *symtab, Elf64_Shdr *shdr)
{
    unsigned int i;
    static unsigned int    gsize = sizeof(globflags) / sizeof(*globflags);

    if (ELF64_ST_BIND(symtab->st_info) == STB_GLOBAL) {
        i = -1;
        while (++i < gsize) {
            if (ELF64_ST_TYPE(symtab->st_info) == globflags[i].stt)
                if (shdr[symtab->st_shndx].sh_type == globflags[i].sh_type)
                    if (shdr[symtab->st_shndx].sh_flags == \
                    globflags[i].sh_flags)
                        return (globflags[i].type);
        }
        return ('U');
    }
    return (0);
}

char local_symbol64(Elf64_Sym *symtab, Elf64_Shdr *shdr)
{
    unsigned int i;
    static unsigned int lsize = sizeof(localflags) / sizeof(*localflags);

    if (ELF64_ST_BIND(symtab->st_info) == STB_LOCAL) {
        i = -1;
        while (++i < lsize) {
            if (ELF64_ST_TYPE(symtab->st_info) == localflags[i].stt)
                if (shdr[symtab->st_shndx].sh_type == localflags[i].sh_type)
                    if (shdr[symtab->st_shndx].sh_flags == \
                    localflags[i].sh_flags)
                        return (localflags[i].type);
        }
    }
    return (0);
}

char c_flag(Elf64_Sym *symtab)
{
    if (ELF64_ST_BIND(symtab->st_info) == STB_GLOBAL)
        if (ELF64_ST_TYPE(symtab->st_info) == STT_OBJECT && \
        symtab->st_shndx == SHN_COMMON)
            return ('C');
    return (0);
}

char weak_symbol64(Elf64_Sym *symtab)
{
    if (ELF64_ST_BIND(symtab->st_info) == STB_WEAK)  {
        if (ELF64_ST_TYPE(symtab->st_info) == STT_OBJECT) {
            if (symtab->st_shndx != SHN_UNDEF)
                return 'V';
            return 'v';
        }
        if (symtab->st_shndx != SHN_UNDEF)
            return 'W';
        return 'w';
    }
    return (0);
}

char set_type(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
    char type = 0;

    if ((type = c_flag(sym)) != 0)
    return (type);
    if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    return ('U');
    if (sym->st_shndx != SHN_ABS && sym->st_shndx != SHN_COMMON) {
        if ((type = global_symbol64(sym, shdr)) != 0)
            return (type);
        if ((type = local_symbol64(sym, shdr)) != 0)
            return (type);
        if ((type = weak_symbol64(sym)) != 0)
            return (type);
        if (sym->st_shndx == SHN_ABS)
            return (ELF64_ST_BIND(sym->st_info) == STB_LOCAL ? 'a' : 'A');
    }
    return ('?');
}