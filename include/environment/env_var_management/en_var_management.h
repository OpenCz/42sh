/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Public API for variable substitution.
** Declares replace_env_vars(char **args, main_t *) which replaces
** every $VAR and ${VAR} token in argv before execution.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

#ifndef ENV_VAR_MANAGEMENT_HPP
    #define ENV_VAR_MANAGEMENT_HPP
char **replace_env_vars(char **args, main_t *stock_main);
#endif
