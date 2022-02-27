/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-mehdi.mourjane
** File description:
** lib
*/

#include "nm.h"

char *my_strcpy(char *str)
{
    char *result = malloc(strlen(str) + 1);
    int i = 0;

    for (i = 0; str[i] != 0; i++) {
        result[i] = str[i];
        if (str[i] > 64 && str[i] < 91)
            result[i] = str[i] + 32;
    }
    result[i] = 0;
    return result;
}

nm_list_t **cook_name(nm_list_t **nm_list)
{
    int i = 0;

    for (int j = 0; nm_list[j] != NULL; j++) {
        for (i = 0; nm_list[j]->name[i] == '_'; i++);
        nm_list[j]->name_cook = my_strcpy(&nm_list[j]->name[i]);
    }
    return nm_list;
}

nm_list_t **print_nm(nm_list_t **nm_list)
{
    for (int j = 0; nm_list[j] != NULL; j++) {
        if (strlen(nm_list[j]->name) == 0)
            continue;
        if (nm_list[j]->value > 0)
            printf ("%016x %c %s\n", nm_list[j]->value, \
            nm_list[j]->type, nm_list[j]->name);
        else
            printf ("                 %c %s\n", nm_list[j]->type, \
            nm_list[j]->name);
    }
}

int check_magic(char *data)
{
    if (data && data[0] == 127 && strncmp(&data[1], "ELF", 3) == 0)
        return 1;
    return 0;
}