/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** cursor.c
*/

#include "c_zsh.h"

char *check_word(int *idx, int i, int *cursor, char **words)
{
    char *actual_word = NULL;

    for (int j = 0; words[i][j] != '\0'; j++) {
        (*idx)++;
        if (*idx == *cursor) {
            actual_word = strdup(words[i]);
            free_array(words);
            return actual_word;
        }
    }
    (*idx)++;
    return NULL;
}

char *get_word_on_cursor(char **buffer, int *cursor)
{
    char **words = my_str_to_word_array(*buffer, " ");
    int idx = 0;
    char *actual_word = NULL;

    if (!words)
        return NULL;
    for (int i = 0; words[i] != NULL; i++){
        actual_word = check_word(&idx, i, cursor, words);
        if (actual_word)
            return actual_word;
    }
    free_array(words);
    return NULL;
}
