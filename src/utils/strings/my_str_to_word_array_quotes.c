/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Quote-aware word splitter: word_state_t tracks in_word and
** in_quote; separator chars inside quotes are ignored; each
** quoted section is kept as one token in the output array.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"
#include <stdlib.h>

static int is_separator(char c, char *separator)
{
    for (int i = 0; separator[i] != '\0'; i++) {
        if (separator[i] == c)
            return 1;
        if (isspace((unsigned char)separator[i]) &&
            isspace((unsigned char)c))
            return 1;
    }
    return 0;
}

static int my_strlen_word_quote(char *str, char *sep)
{
    int count = 0;
    int in_quotes = 0;
    int in_backticks = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '"')
            in_quotes = !in_quotes;
        if (str[i] == '`')
            in_backticks = !in_backticks;
        if (!in_quotes && !in_backticks && is_separator(str[i], sep))
            return count;
        count++;
    }
    return count;
}

static void update_word_state(char c, char *sep, word_state_t *state)
{
    int is_quote = (c == '"' || c == '`');

    if (is_quote) {
        if (c == '"')
            state->in_quotes = !(state->in_quotes);
        else
            state->in_backticks = !(state->in_backticks);
        return;
    }
    if (!state->in_quotes && !state->in_backticks && is_separator(c, sep)) {
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
    word_state_t state = {0, 0, 0, 0};

    if (!str)
        return 0;
    for (int i = 0; str[i] != '\0'; i++)
        update_word_state(str[i], separator, &state);
    return state.count;
}

static void fill_word(char *src, char *sep, char *dst, int len)
{
    int quotes = 0;
    int ticks = 0;
    int j = 0;
    int i = 0;

    while (j < len && src[i]) {
        if (src[i] == '"')
            quotes = !quotes;
        if (src[i] == '`')
            ticks = !ticks;
        if (!quotes && !ticks && is_separator(src[i], sep))
            break;
        dst[j] = src[i];
        j = j + 1;
        i = i + 1;
    }
    dst[j] = '\0';
}

static char *my_strdup_word_quote(char *src, char *sep)
{
    int len = my_strlen_word_quote(src, sep);
    char *word = malloc(sizeof(char) * (len + 1));

    if (!word)
        return NULL;
    fill_word(src, sep, word, len);
    return word;
}

static void advance_word_iter(char *str, char *sep, word_iter_t *iter)
{
    for (; str[iter->pos]; iter->pos++) {
        if (str[iter->pos] == '"')
            iter->iq = !iter->iq;
        if (str[iter->pos] == '`')
            iter->ib = !iter->ib;
        if (iter->iq || iter->ib)
            continue;
        if (is_separator(str[iter->pos], sep))
            break;
    }
}

static void skip_separators(char *str, char *sep, word_iter_t *iter)
{
    for (; !iter->iq && !iter->ib && str[iter->pos] &&
        is_separator(str[iter->pos], sep); iter->pos++);
}

char **my_str_to_word_array_quote(char *str, char *separator)
{
    int words = count_word_quote(str, separator);
    char **word_array = malloc(sizeof(char *) * (words + 1));
    word_iter_t iter = {0, 0, 0};
    int i = 0;

    if (!str || !word_array)
        return NULL;
    for (; i < words; i++) {
        skip_separators(str, separator, &iter);
        word_array[i] = my_strdup_word_quote(str + iter.pos, separator);
        advance_word_iter(str, separator, &iter);
    }
    word_array[i] = NULL;
    return word_array;
}
