/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Time display: display_time prints current HH:MM right-aligned
** using terminal column count from ioctl(TIOCGWINSZ).
** check_null_win falls back to 80 columns when ioctl fails.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../../../include/utils/utils.h"

static int get_size_long_format(struct tm *tm)
{
    char *days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday"};
    char *month[12] = {"January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October", "November",
        "December"};
    int size = my_strlen(days[tm->tm_wday]) + my_strlen(month[tm->tm_mon])
        + len_nb(tm->tm_mday) + len_nb(tm->tm_year + 1900) + 3;

    if (tm->tm_mday < 10)
        size++;
    return size;
}

static int get_size_numeric_format(struct tm *tm)
{
    int size = len_nb(tm->tm_mday) + len_nb(tm->tm_mon)
        + len_nb(tm->tm_year + 1900) + 2;

    if (tm->tm_mday < 10)
        size++;
    if (tm->tm_mon < 10)
        size++;
    return size;
}

static int get_size_date(struct tm *tm, date_format_t date_format)
{
    switch (date_format) {
        case LONG:
            return get_size_long_format(tm);
        case EU:
        case US:
        case ISO:
            return get_size_numeric_format(tm);
    }
    return 0;
}

static void long_date_format(struct tm *tm)
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

static void european_date_format(struct tm *tm)
{
    display_zero(tm->tm_mday);
    write(1, "/", 1);
    display_zero(tm->tm_mon + 1);
    write(1, "/", 1);
    my_putnbr(tm->tm_year + 1900);
    my_putstr(" ");
}

static void us_date_format(struct tm *tm)
{
    display_zero(tm->tm_mon + 1);
    write(1, "/", 1);
    display_zero(tm->tm_mday);
    write(1, "/", 1);
    my_putnbr(tm->tm_year + 1900);
    my_putstr(" ");
}

static void iso_date_format(struct tm *tm)
{
    my_putnbr(tm->tm_year + 1900);
    write(1, "-", 1);
    display_zero(tm->tm_mon + 1);
    write(1, "-", 1);
    display_zero(tm->tm_mday);
    my_putstr(" ");
}

static int check_null_win(int has_win, struct winsize *w, int col)
{
    if (has_win) {
        col = w->ws_col - 8;
        if (col < 1)
            col = 1;
    }
    return col;
}

static void choose_date(struct tm *tm, date_format_t date_format)
{
    switch (date_format) {
        case LONG:
            long_date_format(tm);
            break;
        case EU:
            european_date_format(tm);
            break;
        case US:
            us_date_format(tm);
            break;
        case ISO:
            iso_date_format(tm);
            break;
    }
}

void display_time(infos_t *time_info, infos_t *date, date_format_t date_format,
    int len_prompt)
{
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    struct winsize w;
    char time_str[9];
    int col = 0;
    int has_win = 0;
    int limit = 0;
    int i = 0;
    int size_date = get_size_date(tm, date_format);

    has_win = (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", tm);
    col = check_null_win(has_win, &w, col);
    limit = w.ws_col - len_prompt - size_date - 5;
    for (i = 0; i < limit; i++)
        my_putstr(" ");
    if (date->toggle) {
        print_bg_color(date->b_color);
        print_fg_color(date->color);
        my_putstr(" 𝄜 ");
        choose_date(tm, date_format);
        my_putstr(" \033[0m");
    }
}
