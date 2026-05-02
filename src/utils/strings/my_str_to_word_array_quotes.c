/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Quote-aware word splitter: tracks in_quote state (0=none, 1=double,
** 2=single); separator chars inside any quoted section are ignored;
** each quoted section is kept as one token in the output array.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"
#include <stdlib.h>

static int separator_has_space(char *separator)
{
    for (int i = 0; separator[i] != '\0'; i++) {
        if (separator[i] == ' ')
            return 1;
    }
    return 0;
}

static int is_separator(char c, char *separator)
{
    if (separator_has_space(separator) && isspace((unsigned char)c))
        return 1;
    for (int i = 0; separator[i] != '\0'; i++) {
        if (separator[i] == c)
            return 1;
    }
    return 0;
}

static int update_quote_state(char c, int *iq)
{
    if (c == '"' && *iq != 2) {
        *iq = (*iq == 1) ? 0 : 1;
        return 1;
    }
    if (c == '\'' && *iq != 1) {
        *iq = (*iq == 2) ? 0 : 2;
        return 1;
    }
    return 0;
}

static int my_strlen_word_quote(char *str, char *separator)
{
    int count = 0;
    int in_quotes = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (update_quote_state(str[i], &in_quotes)) {
            count++;
            continue;
        }
        if (!in_quotes && is_separator(str[i], separator))
            return count;
        count++;
    }
    return count;
}

static void update_word_state(char c, char *sep, word_state_t *state)
{
    if (update_quote_state(c, &state->in_quotes))
        return;
    if (!state->in_quotes && is_separator(c, sep)) {
        state->in_word = 0;
        return;
    }
    if (!state->in_word) {
        state->in_word = 1;
        state->count++;
    }
}

static int count_word_quote(char *str, char *separator)
{
    word_state_t state = {0, 0, 0};

    if (!str)
        return 0;
    for (int i = 0; str[i] != '\0'; i++)
        update_word_state(str[i], separator, &state);
    return state.count;
}

static void fill_word(char *to_dup, char *separator, char *word, int len)
{
    int in_quotes = 0;
    int j = 0;

    for (int i = 0; j < len; i++) {
        if (update_quote_state(to_dup[i], &in_quotes)) {
            word[j] = to_dup[i];
            j++;
            continue;
        }
        if (!in_quotes && is_separator(to_dup[i], separator))
            break;
        word[j] = to_dup[i];
        j++;
    }
    word[j] = '\0';
}

static char *my_strdup_word_quote(char *to_dup, char *separator)
{
    int len = my_strlen_word_quote(to_dup, separator);
    char *word = malloc(sizeof(char) * (len + 1));

    if (!word)
        return NULL;
    fill_word(to_dup, separator, word, len);
    return word;
}

static void advance_decalage(char *str, char *sep, int *decalage, int *iq)
{
    while (str[*decalage] && (*iq || !is_separator(str[*decalage], sep))) {
        update_quote_state(str[*decalage], iq);
        (*decalage)++;
    }
}

char **my_str_to_word_array_quote(char *str, char *separator)
{
    int words = count_word_quote(str, separator);
    char **word_array = malloc(sizeof(char *) * (words + 1));
    int decalage = 0;
    int in_quotes = 0;
    int i = 0;

    if (!word_array || !str) {
        free_alloc(word_array);
        return NULL;
    }
    while (i < words) {
        while (!in_quotes && is_separator(str[decalage], separator))
            decalage++;
        word_array[i] = my_strdup_word_quote(str + decalage, separator);
        advance_decalage(str, separator, &decalage, &in_quotes);
        i++;
    }
    word_array[i] = NULL;
    return word_array;
}
