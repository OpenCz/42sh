/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/utils/io
** File description:
** display_zero
*/

#include "../../../include/utils/utils.h"

void display_zero(int nb)
{
    if (nb < 10)
        my_putstr("0");
    my_putnbr(nb);
}
