/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Low-level I/O: my_putchar writes one char to a file descriptor
** (1 stdout, 2 stderr); my_putstr iterates a string to stdout;
** my_putstrerror writes the string to stderr (fd 2).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

void my_putchar(char c, int sortie)
{
    write(sortie, &c, 1);
}

void my_putstr(char *str)
{
    if (!str)
        return;
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i], 1);
    }
}

void my_putstrerror(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i], 2);
    }
}
