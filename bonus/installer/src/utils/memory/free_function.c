/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Full memory cleanup: free_alloc (NULL-safe free), free_array
** (char** + each element), free_linked_list (env_t chain),
** free_history (doubly-linked list), free_main (full teardown).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "installer/install.h"

void free_alloc(void *object)
{
    if (object)
        free(object);
    object = NULL;
}

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free_alloc(array[i]);
    free_alloc(array);
}
