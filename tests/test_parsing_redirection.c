/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_parsing_redirection
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

Test(get_redirection, finds_double_out)
{
    cr_assert_str_eq(get_redirection("echo hi >> out.txt"), ">>");
}

Test(get_redirection, finds_double_in)
{
    cr_assert_str_eq(get_redirection("cat << EOF"), "<<");
}

Test(get_redirection, returns_null_when_absent)
{
    cr_assert_null(get_redirection("echo hello"));
}

// Tests for manage_quotes.c
Test(convert_quotes, handles_simple_string_no_quotes)
{
    char *result = convert_quotes("hello");
    cr_assert_str_eq(result, "hello");
    free(result);
}

Test(convert_quotes, handles_string_with_empty_quotes)
{
    char *result = convert_quotes("hello\"\"world");
    cr_assert_str_eq(result, "helloworld");
    free(result);
}

Test(convert_quotes, handles_escaped_newline_in_quotes)
{
    char *result = convert_quotes("\"hello\\nworld\"");
    char expected[] = "hello\nworld";
    cr_assert_str_eq(result, expected);
    free(result);
}

Test(convert_quotes, handles_escaped_tab_in_quotes)
{
    char *result = convert_quotes("\"hello\\tworld\"");
    char expected[] = "hello\tworld";
    cr_assert_str_eq(result, expected);
    free(result);
}

Test(convert_quotes, handles_escaped_backslash_in_quotes)
{
    char *result = convert_quotes("\"hello\\\\world\"");
    char expected[] = "hello\\world";
    cr_assert_str_eq(result, expected);
    free(result);
}

Test(convert_quotes, handles_escaped_quote_in_quotes)
{
    char *result = convert_quotes("\"hello\\\"world\"");
    char expected[] = "hello\"world";
    cr_assert_str_eq(result, expected);
    free(result);
}

Test(convert_quotes, handles_quotes_with_content)
{
    char *result = convert_quotes("hello\"world\"");
    cr_assert_str_eq(result, "helloworld");
    free(result);
}

Test(convert_quotes, handles_multiple_quoted_sections)
{
    char *result = convert_quotes("\"hello\"world\"test\"");
    cr_assert_str_eq(result, "helloworldtest");
    free(result);
}

Test(convert_quotes, handles_non_special_escape_in_quotes)
{
    char *result = convert_quotes("\"hello\\xworld\"");
    // \x is not recognized, so returns 'x'
    cr_assert_str_eq(result, "helloxworld");
    free(result);
}

Test(convert_quotes, no_escape_without_quotes)
{
    char *result = convert_quotes("hello\\nworld");
    // Without quotes, escapes are not interpreted
    cr_assert_str_eq(result, "hello\\nworld");
    free(result);
}

Test(convert_quotes, handles_escaped_bell_in_quotes)
{
    char *result = convert_quotes("\"hello\\aworld\"");
    char expected[] = "hello\aworld";
    cr_assert_str_eq(result, expected);
    free(result);
}

Test(convert_quotes, handles_escaped_backspace_in_quotes)
{
    char *result = convert_quotes("\"hello\\bworld\"");
    char expected[] = "hello\bworld";
    cr_assert_str_eq(result, expected);
    free(result);
}

Test(convert_quotes, handles_escaped_formfeed_in_quotes)
{
    char *result = convert_quotes("\"hello\\fworld\"");
    char expected[] = "hello\fworld";
    cr_assert_str_eq(result, expected);
    free(result);
}

Test(convert_quotes, handles_escaped_vertical_tab_in_quotes)
{
    char *result = convert_quotes("\"hello\\vworld\"");
    char expected[] = "hello\vworld";
    cr_assert_str_eq(result, expected);
    free(result);
}
