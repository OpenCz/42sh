/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Integer output: my_putnbr writes the sign if negative, then
** recursively decomposes the absolute value into decimal digits
** and writes each to stdout via write(1); INT_MIN is not handled.
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
