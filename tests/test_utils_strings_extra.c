/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_utils_strings_extra
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"

/* ─── my_str_to_word_array_quote ─────────────────────────────────────────── */

Test(my_str_to_word_array_quote, splits_simple_words)
{
    char **arr = my_str_to_word_array_quote("hello world", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "hello");
    cr_assert_str_eq(arr[1], "world");
    cr_assert_null(arr[2]);
    free_array(arr);
}

Test(my_str_to_word_array_quote, keeps_space_inside_double_quotes)
{
    char **arr = my_str_to_word_array_quote("\"hello world\" foo", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "\"hello world\"");
    cr_assert_str_eq(arr[1], "foo");
    cr_assert_null(arr[2]);
    free_array(arr);
}

Test(my_str_to_word_array_quote, returns_null_for_null_input)
{
    cr_assert_null(my_str_to_word_array_quote(NULL, " "));
}

Test(my_str_to_word_array_quote, handles_empty_string)
{
    char **arr = my_str_to_word_array_quote("", " ");

    cr_assert_not_null(arr);
    cr_assert_null(arr[0]);
    free_array(arr);
}

Test(my_str_to_word_array_quote, single_word_no_separator)
{
    char **arr = my_str_to_word_array_quote("onlyone", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "onlyone");
    cr_assert_null(arr[1]);
    free_array(arr);
}

Test(my_str_to_word_array_quote, splits_pipeline_segments)
{
    char **arr = my_str_to_word_array_quote("true|false", "|");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "true");
    cr_assert_str_eq(arr[1], "false");
    cr_assert_null(arr[2]);
    free_array(arr);
}

/* ─── my_str_to_array_of_word_array ─────────────────────────────────────── */

static void free_array_of_word_arrays(char ***arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i]; i++)
        free_array(arr[i]);
    free(arr);
}

Test(my_str_to_array_of_word_array, basic_split, .init = cr_redirect_stderr)
{
    char ***arr = my_str_to_array_of_word_array("ls /tmp;echo hi", ";", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0][0], "ls");
    cr_assert_str_eq(arr[0][1], "/tmp");
    cr_assert_str_eq(arr[1][0], "echo");
    cr_assert_str_eq(arr[1][1], "hi");
    cr_assert_null(arr[2]);
    free_array_of_word_arrays(arr);
}

Test(my_str_to_array_of_word_array, single_segment, .init = cr_redirect_stderr)
{
    char ***arr = my_str_to_array_of_word_array("ls /tmp", ";", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0][0], "ls");
    cr_assert_str_eq(arr[0][1], "/tmp");
    cr_assert_null(arr[1]);
    free_array_of_word_arrays(arr);
}

Test(my_str_to_array_of_word_array, null_str_returns_null,
    .init = cr_redirect_stderr)
{
    cr_assert_null(my_str_to_array_of_word_array(NULL, ";", " "));
}

Test(my_str_to_array_of_word_array, null_sep_ext_returns_null,
    .init = cr_redirect_stderr)
{
    cr_assert_null(my_str_to_array_of_word_array("hello", NULL, " "));
}

Test(my_str_to_array_of_word_array, empty_sep_ext_returns_null,
    .init = cr_redirect_stderr)
{
    cr_assert_null(my_str_to_array_of_word_array("hello", "", " "));
}
