/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Terminal raw mode: init_termios saves the original termios
** state and clears ICANON and ECHO flags for character-by-
** character input; caller must restore the saved state after.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

void init_termios(struct termios *tr, struct termios *old)
{
    tcgetattr(STDIN_FILENO, old);
    tcgetattr(STDIN_FILENO, tr);
    tr->c_lflag &= ~(ICANON | ECHO | ISIG);
    tr->c_cc[VMIN] = 1;
    tr->c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, tr);
}
