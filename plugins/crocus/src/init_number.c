/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/pre-release/minishell
** File description:
** mysh
*/

#include "crocus.h"

number_t *five(void)
{
    number_t *number = malloc(sizeof(number_t));

    if (!number)
        return NULL;
    number->line1 = strdup("00000");
    number->line2 = strdup("0    ");
    number->line3 = strdup("0000 ");
    number->line4 = strdup("    0");
    number->line5 = strdup("0000 ");
    if (!number->line1 || !number->line2
        || !number->line3 || !number->line4
        || !number->line5)
        return NULL;
    return number;
}

number_t *six(void)
{
    number_t *number = malloc(sizeof(number_t));

    if (!number)
        return NULL;
    number->line1 = strdup(" 000 ");
    number->line2 = strdup("0    ");
    number->line3 = strdup("0000 ");
    number->line4 = strdup("0   0");
    number->line5 = strdup(" 000 ");
    if (!number->line1 || !number->line2
        || !number->line3 || !number->line4
        || !number->line5)
        return NULL;
    return number;
}

number_t *seven(void)
{
    number_t *number = malloc(sizeof(number_t));

    if (!number)
        return NULL;
    number->line1 = strdup("00000");
    number->line2 = strdup("    0");
    number->line3 = strdup("   0 ");
    number->line4 = strdup("  0  ");
    number->line5 = strdup(" 0   ");
    if (!number->line1 || !number->line2
        || !number->line3 || !number->line4
        || !number->line5)
        return NULL;
    return number;
}

number_t *eight(void)
{
    number_t *number = malloc(sizeof(number_t));

    if (!number)
        return NULL;
    number->line1 = strdup(" 000 ");
    number->line2 = strdup("0   0");
    number->line3 = strdup(" 000 ");
    number->line4 = strdup("0   0");
    number->line5 = strdup(" 000 ");
    if (!number->line1 || !number->line2
        || !number->line3 || !number->line4
        || !number->line5)
        return NULL;
    return number;
}

number_t *nine(void)
{
    number_t *number = malloc(sizeof(number_t));

    if (!number)
        return NULL;
    number->line1 = strdup(" 000 ");
    number->line2 = strdup("0   0");
    number->line3 = strdup(" 0000");
    number->line4 = strdup("    0");
    number->line5 = strdup(" 000 ");
    if (!number->line1 || !number->line2
        || !number->line3 || !number->line4
        || !number->line5)
        return NULL;
    return number;
}
