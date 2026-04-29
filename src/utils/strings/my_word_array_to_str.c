/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** my_word_array_to_str
*/

#include "../../../include/c_zsh.h"

static int get_total_len(char **array)
{
    int total = 0;

    for (int i = 0; array[i]; i++)
        total += strlen(array[i]) + (i > 0 ? 1 : 0);
    return total;
}

char *my_word_array_to_str(char **array)
{
    char *str = NULL;
    int total_len = 0;

    if (!array || !array[0])
        return NULL;
    total_len = get_total_len(array);
    str = malloc(sizeof(char) * (total_len + 1));
    if (!str)
        return NULL;
    str[0] = '\0';
    for (int i = 0; array[i]; i++) {
        if (i > 0)
            strcat(str, " ");
        strcat(str, array[i]);
    }
    return str;
}
