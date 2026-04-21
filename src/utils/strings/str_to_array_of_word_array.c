/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** str_to_array_of_word_array
*/

#include "../../../include/c_zsh.h"

static void write_error(char const *msg)
{
    fputs(msg, stderr);
}

static int count_words(char const *str, char const *sep)
{
    int count = 0;

    if (!str || !sep || sep[0] == '\0')
        return 0;
    while (*str != '\0') {
        str += strspn(str, sep);
        if (*str == '\0')
            break;
        count++;
        str += strcspn(str, sep);
    }
    return count;
}

static int check_inputs(char const *str, char const *sep, const char *label)
{
    if (!str) {
        write_error("ERROR: ");
        write_error(label);
        write_error(": NULL string\n");
        return -1;
    }
    if (!sep) {
        write_error("ERROR: ");
        write_error(label);
        write_error(": NULL separator\n");
        return -1;
    }
    if (sep[0] == '\0') {
        write_error("ERROR: ");
        write_error(label);
        write_error(": empty separator\n");
        return -1;
    }
    return 0;
}

static void free_array_of_word_array(char ***arr, int filled)
{
    int i;

    if (!arr)
        return;
    for (i = 0; i < filled; i++) {
        if (arr[i])
            free_array(arr[i]);
    }
    free(arr);
}

static char *dup_segment(char const *str, int len)
{
    char *seg;

    if (!str || len < 0) {
        write_error("ERROR: dup_segment: invalid input\\n");
        return NULL;
    }
    seg = malloc(sizeof(char) * (len + 1));
    if (!seg) {
        write_error("ERROR: dup_segment: malloc failure\n");
        return NULL;
    }
    memcpy(seg, str, (size_t)len);
    seg[len] = '\0';
    return seg;
}

static char **fill_slot(char const *str, char const *sep_ext,
    char const *sep_int)
{
    char **slot;
    char *seg;
    int len;

    if (!str || !sep_ext || !sep_int) {
        write_error("ERROR: fill_slot: invalid input\\n");
        return NULL;
    }
    len = (int)strcspn(str, sep_ext);
    seg = dup_segment(str, len);
    if (!seg)
        return NULL;
    slot = my_str_to_word_array(seg, (char *)sep_int);
    free(seg);
    if (!slot)
        write_error("ERROR: fill_slot: my_str_to_word_array failure\n");
    return slot;
}

static char ***loop_filling(char ***arr, char const *str,
    char const *sep_ext, char const *sep_int)
{
    int n = count_words(str, sep_ext);
    int i;

    if (!arr || !str || !sep_ext || !sep_int) {
        write_error("ERROR: loop_filling: invalid input\\n");
        free_array_of_word_array(arr, 0);
        return NULL;
    }
    str += strspn(str, sep_ext);
    for (i = 0; i < n; i++) {
        arr[i] = fill_slot(str, sep_ext, sep_int);
        if (!arr[i]) {
            free_array_of_word_array(arr, i);
            return NULL;
        }
        str += strcspn(str, sep_ext);
        str += strspn(str, sep_ext);
    }
    arr[n] = NULL;
    return arr;
}

static char ***alloc_array(int n)
{
    char ***arr;

    if (n < 0) {
        write_error("ERROR: alloc_array: invalid size\\n");
        return NULL;
    }
    arr = calloc((size_t)(n + 1), sizeof(char **));
    if (!arr) {
        write_error("ERROR: alloc_array: malloc failure\n");
        return NULL;
    }
    return arr;
}

char ***my_str_to_array_of_word_array(char const *str, char const *sep_ext,
    char const *sep_int)
{
    char ***arr;
    int n;

    if (check_inputs(str, sep_ext, "my_str_to_array_of_word_array") == -1)
        return NULL;
    if (check_inputs(str, sep_int, "my_str_to_array_of_word_array") == -1)
        return NULL;
    n = count_words(str, sep_ext);
    if (n == 0) {
        write_error("ERROR: my_str_to_array_of_word_array: no words found\n");
        return NULL;
    }
    arr = alloc_array(n);
    if (!arr)
        return NULL;
    return loop_filling(arr, str, sep_ext, sep_int);
}
