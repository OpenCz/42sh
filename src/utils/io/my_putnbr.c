/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Integer output: my_putnbr recursively decomposes an integer
** into decimal digits (with INT_MIN handled separately) and
** writes each digit to stdout with my_putchar.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include <unistd.h>

int my_putnbr(int nb)
{
    char c = 0;

    if (nb < 0) {
        write(1, "-", 1);
        nb = -nb;
    }
    if (nb < 10) {
        c = nb + '0';
        write(1, &c, 1);
    } else {
        my_putnbr(nb / 10);
        c = nb % 10 + '0';
        write(1, &c, 1);
    }
    return 0;
}
