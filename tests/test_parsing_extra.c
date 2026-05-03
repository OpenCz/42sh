/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_parsing_extra
** Additional parsing tests: get_redirection single operators,
** convert_quotes escape sequences, decode_literals edge cases,
** my_strstr quote-awareness.
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"
Test(get_redirection_extra, finds_single_redirect_out)
{
    cr_assert_str_eq(get_redirection("echo hi > out.txt"), ">");
}

Test(get_redirection_extra, finds_single_redirect_in)
{
    cr_assert_str_eq(get_redirection("cat < input.txt"), "<");
}

Test(get_redirection_extra, double_operator_takes_priority_over_single)
{
    const char *r = get_redirection("echo hi >> out.txt");

    cr_assert_str_eq(r, ">>");
}

Test(get_redirection_extra, heredoc_takes_priority_over_single_in)
{
    const char *r = get_redirection("cat << EOF");

    cr_assert_str_eq(r, "<<");
}

Test(get_redirection_extra, no_operator_returns_null)
{
    cr_assert_null(get_redirection("ls -la"));
}

Test(get_redirection_extra, empty_string_returns_null)
{
    cr_assert_null(get_redirection(""));
}

Test(get_redirection_extra, operator_at_start_of_string)
{
    cr_assert_not_null(get_redirection("> file.txt"));
}
Test(convert_quotes_extra, escape_r_inside_double_quotes)
{
    char *result = convert_quotes("\"\\r\"");

    cr_assert_not_null(result);
    cr_assert_eq(result[0], '\r');
    cr_assert_eq(result[1], '\0');
    free(result);
}

Test(convert_quotes_extra, escape_a_inside_double_quotes)
{
    char *result = convert_quotes("\"\\a\"");

    cr_assert_not_null(result);
    cr_assert_eq(result[0], '\a');
    cr_assert_eq(result[1], '\0');
    free(result);
}

Test(convert_quotes_extra, unknown_escape_kept_as_is)
{
    char *result = convert_quotes("\"\\z\"");

    cr_assert_not_null(result);
    cr_assert_eq(result[0], 'z');
    free(result);
}

Test(convert_quotes_extra, single_quotes_preserve_backslash)
{
    char *result = convert_quotes("'hello\\nworld'");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "hello\\nworld");
    free(result);
}

Test(convert_quotes_extra, double_quotes_with_embedded_dollar)
{
    char *result = convert_quotes("\"$HOME\"");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "$HOME");
    free(result);
}

Test(convert_quotes_extra, mixed_single_then_double)
{
    char *result = convert_quotes("'a'\"b\"");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "ab");
    free(result);
}

Test(convert_quotes_extra, nested_single_in_unquoted_context)
{
    char *result = convert_quotes("'hello world'");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "hello world");
    free(result);
}

Test(convert_quotes_extra, no_quotes_passthrough)
{
    char *result = convert_quotes("no quotes here");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "no quotes here");
    free(result);
}
Test(decode_literals_extra, null_returns_null)
{
    cr_assert_null(decode_literals(NULL));
}

Test(decode_literals_extra, empty_string_returns_empty)
{
    char *result = decode_literals("");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "");
    free(result);
}

Test(decode_literals_extra, no_sentinel_unchanged)
{
    char *result = decode_literals("hello world");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "hello world");
    free(result);
}

Test(decode_literals_extra, multiple_sentinels_replaced)
{
    char *result = decode_literals("\x01" "A \x01" "B");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "$A $B");
    free(result);
}

Test(decode_literals_extra, sentinel_at_start)
{
    char *result = decode_literals("\x01" "HOME");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "$HOME");
    free(result);
}

Test(decode_literals_extra, sentinel_at_end)
{
    char *result = decode_literals("echo \x01");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "echo $");
    free(result);
}
Test(my_strstr_extra, not_found_returns_null)
{
    cr_assert_null(my_strstr("hello world", "xyz"));
}

Test(my_strstr_extra, empty_needle_returns_haystack)
{
    const char *h = "hello";
    const char *r = my_strstr(h, "");

    cr_assert_ptr_eq(r, h);
}

Test(my_strstr_extra, skips_match_inside_double_quotes)
{
    cr_assert_null(my_strstr("echo \"world\" end", "world"));
}

Test(my_strstr_extra, finds_match_outside_quotes)
{
    const char *r = my_strstr("echo \"skip\" world", "world");

    cr_assert_not_null(r);
    cr_assert_str_eq(r, "world");
}
