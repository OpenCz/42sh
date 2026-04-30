/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Word array length: my_wordarray_len iterates a NULL-terminated
** char** and returns the element count before the sentinel.
** Returns 0 for NULL input or an immediately-NULL-terminated array.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

int my_wordarray_len(char **word_array)
{
    int i = 0;

    if (word_array == NULL)
        return 0;
    for (i = 0; word_array[i] != NULL; i++);
    return i;
}
