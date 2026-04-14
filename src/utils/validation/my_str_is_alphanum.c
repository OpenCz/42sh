/*
** EPITECH PROJECT, 2026
** my_str_to_alphanum
** File description:
** num
*/

#include "42sh.h"

int my_str_is_alphanum(char *key)
{
    int i = 0;

    while (key[i] != '\0') {
        if (!((key[i] >= '0' && key[i] <= '9') ||
                (key[i] >= 'A' && key[i] <= 'Z') ||
                (key[i] >= 'a' && key[i] <= 'z'))) {
            return 1;
        }
        i++;
    }
    return SUCCESS;
}
