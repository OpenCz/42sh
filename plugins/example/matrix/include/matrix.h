/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/pre-release/minishell
** File description:
** mysh
*/

#ifndef MATRIX_H
    #define MATRIX_H

void set_blank_term(void);
void get_terminal_size(int *rows, int *cols);
void restore_terminal(struct termios *old);

#endif
