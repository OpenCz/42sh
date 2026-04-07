/*
** EPITECH PROJECT, 2026
** my_strconcat
** File description:
** strconcat
*/

#include "minishell.h"

char *my_strconcat(char *str1, char *str2)
{
    int i = 0;
    int j = 0;
    int len = my_strlen(str1) + my_strlen(str2);
    char *result = malloc(sizeof(char) * (len + 1));

    for (; str1[i] != '\0'; i++) {
        result[j] = str1[i];
        j++;
    }
    for (i = 0; str2[i] != '\0'; i++) {
        result[j] = str2[i];
        j++;
    }
    result[j] = '\0';
    return result;
}
