/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Public API for memory cleanup: free_alloc (NULL-safe free),
** free_array (char**), free_linked_list (env_t chain),
** free_main (full main_t teardown including history and RC).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#ifndef MEMORY_H
    #define MEMORY_H

    #include "core/types.h"

void free_linked_list(env_t *env);
void free_array(char **array);
void free_main(main_t *stock);
void free_alloc(void *object);

#endif
