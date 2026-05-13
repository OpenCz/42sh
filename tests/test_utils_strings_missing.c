/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_utils_strings_missing
** Covers: my_itoa, my_word_array_to_str, is_escaped, unmatched_quote,
**         my_str_is_alpha
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include "../include/c_zsh.h"
Test(my_itoa, zero)
{
    char *s = my_itoa(0);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "0");
    free(s);
}

Test(my_itoa, positive_single_digit)
{
    char *s = my_itoa(7);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "7");
    free(s);
}

Test(my_itoa, positive_multi_digit)
{
    char *s = my_itoa(42);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "42");
    free(s);
}

Test(my_itoa, large_positive)
{
    char *s = my_itoa(2147483647);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "2147483647");
    free(s);
}

Test(my_itoa, negative_single_digit)
{
    char *s = my_itoa(-1);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "-1");
    free(s);
}

Test(my_itoa, negative_multi_digit)
{
    char *s = my_itoa(-42);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "-42");
    free(s);
}

Test(my_itoa, int_min)
{
    char *s = my_itoa(INT_MIN);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "-2147483648");
    free(s);
}

Test(my_itoa, hundred)
{
    char *s = my_itoa(100);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "100");
    free(s);
}

Test(my_itoa, negative_hundred)
{
    char *s = my_itoa(-100);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "-100");
    free(s);
}
Test(my_word_array_to_str, joins_with_spaces)
{
    char *arr[] = {"hello", "world", NULL};
    char *s = my_word_array_to_str(arr);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "hello world");
    free(s);
}

Test(my_word_array_to_str, single_element)
{
    char *arr[] = {"only", NULL};
    char *s = my_word_array_to_str(arr);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "only");
    free(s);
}

Test(my_word_array_to_str, three_elements)
{
    char *arr[] = {"a", "b", "c", NULL};
    char *s = my_word_array_to_str(arr);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "a b c");
    free(s);
}

Test(my_word_array_to_str, null_array_returns_null)
{
    cr_assert_null(my_word_array_to_str(NULL));
}

Test(my_word_array_to_str, empty_first_elem_returns_null)
{
    char *arr[] = {NULL};

    cr_assert_null(my_word_array_to_str(arr));
}
Test(is_escaped, no_backslash_not_escaped)
{
    char str[] = "abc";

    cr_assert_eq(is_escaped(str, 2), 0);
}

Test(is_escaped, single_backslash_is_escaped)
{
    char str[] = "a\\b";

    cr_assert_eq(is_escaped(str, 2), 1);
}

Test(is_escaped, double_backslash_not_escaped)
{
    char str[] = "a\\\\b";

    cr_assert_eq(is_escaped(str, 4), 0);
}

Test(is_escaped, triple_backslash_is_escaped)
{
    char str[] = "a\\\\\\b";

    cr_assert_eq(is_escaped(str, 4), 1);
}

Test(is_escaped, at_index_zero_not_escaped)
{
    char str[] = "abc";

    cr_assert_eq(is_escaped(str, 0), 0);
}

Test(is_escaped, backslash_at_start_not_escaped)
{
    char str[] = "\\a";

    cr_assert_eq(is_escaped(str, 1), 1);
}
Test(unmatched_quote, double_quote_prints_to_stderr)
{
    void *result = unmatched_quote(1, NULL);

    cr_assert_null(result);
}

Test(unmatched_quote, single_quote_prints_to_stderr)
{
    void *result = unmatched_quote(2, NULL);

    cr_assert_null(result);
}

Test(unmatched_quote, frees_word_array_and_returns_null,
    .init = cr_redirect_stderr)
{
    char **arr = malloc(sizeof(char *) * 2);

    cr_assert_not_null(arr);
    arr[0] = strdup("hello");
    arr[1] = NULL;
    cr_assert_null(unmatched_quote(1, arr));
}
Test(my_str_is_alpha, all_digits_returns_success)
{
    cr_assert_eq(my_str_is_alpha("123"), SUCCESS);
}

Test(my_str_is_alpha, empty_string_returns_success)
{
    cr_assert_eq(my_str_is_alpha(""), SUCCESS);
}

Test(my_str_is_alpha, single_digit_returns_success)
{
    cr_assert_eq(my_str_is_alpha("9"), SUCCESS);
}

Test(my_str_is_alpha, letter_returns_failure)
{
    cr_assert_eq(my_str_is_alpha("abc"), 1);
}

Test(my_str_is_alpha, mixed_returns_failure)
{
    cr_assert_eq(my_str_is_alpha("1a2"), 1);
}

Test(my_str_is_alpha, underscore_returns_failure)
{
    cr_assert_eq(my_str_is_alpha("_"), 1);
}
