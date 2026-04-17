/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** shell
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#ifndef MINISHELL_H
    #define MINISHELL_H

    #include "core/types.h"
    #include "core/core.h"
    #include "utils/utils.h"
    #include "utils/defines.h"
    #include "environment/environment.h"
    #include "environment/env_var_management/en_var_management.h"
    #include "parsing/parsing.h"
    #include "builtins/builtins.h"
    #include "execution/execution.h"
    #include "memory/memory.h"
    #include "config/czshrc.h"

#endif
