/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** memory api
*/

#ifndef MEMORY_H
    #define MEMORY_H

    #include "core/types.h"

void free_linked_list(env_t *env);
void free_array(char **array);
void free_main(main_t *stock);
void free_shell_state(main_t *stock);

#endif
