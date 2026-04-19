/*
** EPITECH PROJECT, 2026
** strstr
** File description:
** str
*/

#include "c_zsh.h"

const char *my_strstr(const char *str, const char *to_f)
{
    int k = 0;
    int in_quote = 0;

    if (*to_f == '\0')
        return str;
    for (int i = 0; str[i] != '\0'; i++) {
        k = 0;
        if (str[i] == '"')
            in_quote = !in_quote;
        if (in_quote)
            continue;
        while (str[i + k] != '\0' && to_f[k] != '\0' && str[i + k] == to_f[k])
            k++;
        if (to_f[k] == '\0')
            return &str[i];
    }
    return NULL;
}
