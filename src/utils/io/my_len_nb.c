/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/utils/io
** File description:
** my_len_nb
*/

int len_nb(int nb)
{
    int len = 0;

    if (nb == 0)
        return 1;
    if (nb < 0) {
        len++;
        nb = -nb;
    }
    while (nb != 0) {
        nb = nb / 10;
        len++;
    }
    return len;
}
