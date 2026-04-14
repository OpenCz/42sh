/*
** EPITECH PROJECT, 2026
** my_strcmp
** File description:
** my_strcmp
*/

#include "c_zsh.h"

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return -1;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0')
            return SUCCESS;
        i++;
    }
    return s1[i] - s2[i];
}
