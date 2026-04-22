/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The foreach.c
*/
/**
 * @file foreach.c
 * @brief The foreach.c
 * @author Erwan Lo Presti
 */

#include "../../../include/c_zsh.h"

int put_error_var(char *var)
{
    my_putstr(var);
    my_putstr(": Undefined variable.\n");
    return FAILURE;
}
