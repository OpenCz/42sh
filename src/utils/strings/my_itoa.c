/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** my_itoa
*/

#include "c_zsh.h"

static size_t get_num_len(int num)
{
    size_t len = 0;

    if (num <= 0)
        len++;
    for (; num; len++)
        num /= 10;
    return len;
}

static void fill_str(char *str, int num, size_t len, int is_negative)
{
    if (num == INT_MIN) {
        for (size_t i = len - 1; i > 0; i--) {
            str[i] = '0' + (-(num % 10));
            num /= 10;
        }
        str[0] = '-';
        return;
    }
    if (is_negative)
        num = -num;
    for (size_t i = len - 1; num; i--) {
        str[i] = (num % 10) + '0';
        num /= 10;
    }
    if (is_negative)
        str[0] = '-';
}

char *my_itoa(int num)
{
    size_t len = get_num_len(num);
    char *str = malloc(len + 1);

    if (!str)
        return NULL;
    str[len] = '\0';
    if (num == 0) {
        str[0] = '0';
        return str;
    }
    fill_str(str, num, len, num < 0);
    return str;
}
