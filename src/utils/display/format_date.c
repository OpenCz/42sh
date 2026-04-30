/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/utils/display
** File description:
** format_date
*/

#include <time.h>
#include "c_zsh.h"

void long_date_format(struct tm *tm)
{
    char *days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday"};
    char *month[12] = {"January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October", "November",
        "December"};

    write(1, days[tm->tm_wday], my_strlen(days[tm->tm_wday]));
    write(1, " ", 1);
    write(1, month[tm->tm_mon], my_strlen(month[tm->tm_mon]));
    write(1, " ", 1);
    display_zero(tm->tm_mday);
    write(1, " ", 1);
    my_putnbr(tm->tm_year + 1900);
    my_putstr(" ");
}

void european_date_format(struct tm *tm)
{
    display_zero(tm->tm_mday);
    write(1, "/", 1);
    display_zero(tm->tm_mon + 1);
    write(1, "/", 1);
    my_putnbr(tm->tm_year + 1900);
    my_putstr(" ");
}

void us_date_format(struct tm *tm)
{
    display_zero(tm->tm_mon + 1);
    write(1, "/", 1);
    display_zero(tm->tm_mday);
    write(1, "/", 1);
    my_putnbr(tm->tm_year + 1900);
    my_putstr(" ");
}

void iso_date_format(struct tm *tm)
{
    my_putnbr(tm->tm_year + 1900);
    write(1, "-", 1);
    display_zero(tm->tm_mon + 1);
    write(1, "-", 1);
    display_zero(tm->tm_mday);
    my_putstr(" ");
}
