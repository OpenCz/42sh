/*
** EPITECH PROJECT, 2026
** my_pputstr
** File description:
** my_putstr
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
