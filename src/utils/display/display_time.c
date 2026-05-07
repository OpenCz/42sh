/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Time/date display: computes right-padding via ioctl(TIOCGWINSZ) and
** calculate_limit, then prints HH:MM:SS via displauy_time() and the date
** in LONG/EU/US/ISO format via display_date(), both with ANSI color support.
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

static void display_date(infos_t *date, struct tm *tm,
    date_format_t date_format)
{
    if (date->toggle) {
        print_bg_color(date->b_color);
        print_fg_color(date->color);
        my_putstr(" 𝄜 ");
        choose_date(tm, date_format);
        my_putstr("\033[0m");
    }
}

static void displauy_time(infos_t *time_info, struct tm *tm, infos_t *date)
{
    if (time_info->toggle) {
        print_bg_color(time_info->b_color);
        print_fg_color(time_info->color);
        my_putstr(" 🕜");
        if (tm->tm_hour < 10)
            my_putstr("0");
        my_putnbr(tm->tm_hour);
        my_putstr(":");
        if (tm->tm_min < 10)
            my_putstr("0");
        my_putnbr(tm->tm_min);
        my_putstr(":");
        if (tm->tm_sec < 10)
            my_putstr("0");
        my_putnbr(tm->tm_sec);
        my_putstr(" \033[0m");
    }
}

static void calculate_limit(infos_t *time_info, infos_t *date, int *limit,
    int size_date)
{
    if (date->toggle) {
        if (!time_info->toggle)
            *limit += 2;
        *limit = *limit - 5 - size_date;
    }
    if (time_info->toggle) {
        if (!date->toggle)
            *limit -= 1;
        *limit -= 10;
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
    limit = w.ws_col - len_prompt - 1;
    calculate_limit(time_info, date, &limit, size_date);
    for (i = 0; i < limit; i++)
        my_putstr(" ");
    displauy_time(time_info, tm, date);
    display_date(date, tm, date_format);
}
