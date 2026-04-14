/*
** EPITECH PROJECT, 2026
** strdup
** File description:
** recode
*/

#include "42sh.h"

char *my_strdup(char *str)
{
    int i = 0;
    int len = my_strlen(str);
    char *dup = malloc(sizeof(char) * (len + 1));

    for (i = 0; str[i] != '\0'; i++)
        dup[i] = str[i];
    dup[i] = '\0';
    return dup;
}
