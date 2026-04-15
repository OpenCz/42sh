/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The display_time.c
*/
/**
 * @file display_time.c
 * @brief The display_time.c
 * @author Erwan Lo Presti
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../../../include/utils/utils.h"

static void long_date_format(struct tm *tm)
{
    char *days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday"};
    char *month[12] = {"January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};

    printf("%s %d %s %d\n", days[tm->tm_wday], tm->tm_mday,
        month[tm->tm_mon], tm->tm_year + 1900);
}

static void european_date_format(struct tm *tm)
{
    printf("%02d/%02d/%d\n", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
}

static void us_date_format(struct tm *tm)
{
    printf("%02d/%02d/%d\n", tm->tm_mon + 1, tm->tm_mday, tm->tm_year + 1900);
}

static void iso_date_format(struct tm *tm)
{
    printf("%d-%02d-%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
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

void display_time(void)
{
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    struct winsize w;
    char time_str[9];
    int col = 0;
    int has_win = 0;

    has_win = (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", tm);
    col = check_null_win(has_win, &w, col);
    long_date_format(tm);
    european_date_format(tm);
    us_date_format(tm);
    iso_date_format(tm);
    if (has_win)
        printf("\033[%dG", col);
    printf("%s\n", time_str);
}
