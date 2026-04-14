/*
** EPITECH PROJECT, 2026
** strstr
** File description:
** str
*/

#include "c_zsh.h"

const char *my_strstr(const char *str, const char *to_f)
{
    int i = 0;
    int k = 0;

    if (*to_f == '\0')
        return str;
    while (str[i] != '\0') {
        k = 0;
        while (str[i + k] != '\0' && to_f[k] != '\0' && str[i + k] == to_f[k]) {
            k++;
        }
        if (to_f[k] == '\0')
            return &str[i];
        i++;
    }
    return NULL;
}
