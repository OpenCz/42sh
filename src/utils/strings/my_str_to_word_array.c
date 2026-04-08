/*
** EPITECH PROJECT, 2026
** sandbox
** File description:
** sandbox
*/

#include "minishell.h"

static int is_separator(char c, char *separator)
{
    for (int i = 0; separator[i] != '\0'; i++) {
        if (separator[i] == c)
            return 1;
    }
    return SUCCESS;
}

static int my_strlen_word_array(char *str, char *separator)
{
    int i = 0;
    int count = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], separator))
            return count;
        if (is_separator(str[i], separator) == 0)
            count++;
    }
    return count;
}

static void update_word_state(char c, char *separator, int *in_word, int *count)
{
    if (is_separator(c, separator) == 1) {
        *in_word = 0;
    } else if (!(*in_word)) {
        *in_word = 1;
        (*count)++;
    }
}

static int count_word(char *str, char *separator)
{
    int in_word = 0;
    int count = 0;

    if (str == NULL)
        return SUCCESS;
    for (int i = 0; str[i] != '\0'; i++) {
        update_word_state(str[i], separator, &in_word, &count);
    }
    return count;
}

char *my_strdup_word_array(char *to_dup, char *separator)
{
    int len = my_strlen_word_array(to_dup, separator);
    char *word = malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (!word)
        return NULL;
    for (i = 0; i < len; i++) {
        word[i] = to_dup[i];
    }
    word[i] = '\0';
    return word;
}

char **my_str_to_word_array(char *str, char *separator)
{
    int words = count_word(str, separator);
    char **word_array = malloc(sizeof(char *) * (words + 1));
    int decalage = 0;
    int i = 0;

    if (!word_array || !str)
        return NULL;
    while (i < words) {
        while (is_separator(str[decalage], separator))
            decalage++;
        word_array[i] = my_strdup_word_array(str + decalage, separator);
        while (str[decalage] && !is_separator(str[decalage], separator))
            decalage++;
        i++;
    }
    word_array[i] = NULL;
    return word_array;
}
