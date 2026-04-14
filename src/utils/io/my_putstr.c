/*
** EPITECH PROJECT, 2026
** my_pputstr
** File description:
** my_putstr
*/

#include "42sh.h"

void my_putchar(char c, int sortie)
{
    write(sortie, &c, 1);
}

void my_putstr(char *str)
{
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
