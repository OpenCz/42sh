/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** String duplication: allocates strlen(str)+1 bytes and copies
** the input character by character into the new buffer.
** Returns NULL if the input pointer is NULL.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

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
