/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Public API for input parsing: get_redirection() scans a command
** for >>, <<, >, < tokens; convert_quotes() strips double-quotes
** and resolves C escape sequences inside quoted tokens.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#ifndef PARSING_H
    #define PARSING_H

char *get_redirection(const char *command);
char *convert_quotes(char *cmd);
char *command_substitution(main_t *stock_main, char *command);


#endif
