/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The my_putnbr.c
*/
/**
 * @file my_putnbr.c
 * @brief The my_putnbr.c
 * @author Erwan Lo Presti
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
