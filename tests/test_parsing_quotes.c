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

Test(convert_quotes, single_quotes_keep_dollar_literal_through_expansion)
{
    env_t node = {.key = "FOO", .value = "bar", .next = NULL};
    main_t stock = {0};
    char **args = malloc(sizeof(char *) * 2);
    char *decoded = NULL;

    cr_assert_not_null(args);
    stock.stock_env = &node;
    args[0] = convert_quotes("'$FOO'");
    args[1] = NULL;
    cr_assert_not_null(args[0]);
    replace_env_vars(args, &stock);
    cr_assert_str_eq(args[0], "\x01" "FOO");
    decoded = decode_literals(args[0]);
    cr_assert_not_null(decoded);
    cr_assert_str_eq(decoded, "$FOO");
    free(decoded);
    free_array(args);
}

Test(decode_literals, restores_sentinel_to_dollar)
{
    char *result = decode_literals("alpha\x01" "beta");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "alpha$beta");
    free(result);
}

