/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The my_char_is_alpha.c
*/
/**
 * @file my_char_is_alpha.c
 * @brief The my_char_is_alpha.c
 * @author Erwan Lo Presti
 */

#include "../../../include/c_zsh.h"

int my_char_is_alpha(char key)
{
    if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))
        return SUCCESS;
    return 1;
}
