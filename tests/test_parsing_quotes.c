/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_parsing_quotes
*/

#include <criterion/criterion.h>
#include "../include/c_zsh.h"

Test(convert_quotes, no_quotes_returns_copy_unchanged)
{
    char *result = convert_quotes("hello world");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "hello world");
    free(result);
}

Test(convert_quotes, removes_double_quotes_around_word)
{
    char *result = convert_quotes("\"hello\"");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "hello");
    free(result);
}

Test(convert_quotes, removes_quotes_preserving_space_inside)
{
    char *result = convert_quotes("\"hello world\"");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "hello world");
    free(result);
}

Test(convert_quotes, escape_n_inside_quotes_becomes_newline)
{
    char *result = convert_quotes("\"\\n\"");

    cr_assert_not_null(result);
    cr_assert_eq(result[0], '\n');
    cr_assert_eq(result[1], '\0');
    free(result);
}

Test(convert_quotes, escape_t_inside_quotes_becomes_tab)
{
    char *result = convert_quotes("\"\\t\"");

    cr_assert_not_null(result);
    cr_assert_eq(result[0], '\t');
    cr_assert_eq(result[1], '\0');
    free(result);
}

Test(convert_quotes, escape_backslash_inside_quotes)
{
    char *result = convert_quotes("\"\\\\\"");

    cr_assert_not_null(result);
    cr_assert_eq(result[0], '\\');
    cr_assert_eq(result[1], '\0');
    free(result);
}

Test(convert_quotes, mixed_quoted_and_unquoted_segments)
{
    char *result = convert_quotes("pre\"mid\"post");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "premidpost");
    free(result);
}

Test(convert_quotes, empty_string_returns_empty)
{
    char *result = convert_quotes("");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "");
    free(result);
}

Test(convert_quotes, empty_quotes_returns_empty)
{
    char *result = convert_quotes("\"\"");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "");
    free(result);
}
