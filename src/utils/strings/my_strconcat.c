/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** String concatenation: allocates strlen(s1)+strlen(s2)+1 bytes
** and copies s1 then s2 into the new buffer.
** Returns the heap-allocated result string.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

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
