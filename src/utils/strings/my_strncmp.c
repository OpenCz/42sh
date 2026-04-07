/*
** EPITECH PROJECT, 2026
** my_strncmo
** File description:
** cmp
*/

#include "minishell.h"

int my_strncmp(char *s1, char *s2, int n)
{
    int i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == '\0' || i == n - 1)
            return 0;
        i++;
    }
    return s1[i] - s2[i];
}
