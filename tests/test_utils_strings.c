/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_utils_strings
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

Test(my_strlen, returns_correct_length)
{
    cr_assert_eq(my_strlen("minishell"), 9);
}

Test(my_strcmp, compares_strings)
{
    cr_assert_eq(my_strcmp("abc", "abc"), 0);
    cr_assert_lt(my_strcmp("abc", "abd"), 0);
}

Test(my_strncmp, compares_up_to_n)
{
    cr_assert_eq(my_strncmp("abcdef", "abcxyz", 3), 0);
    cr_assert_gt(my_strncmp("aby", "abx", 3), 0);
}

Test(my_strdup, duplicates_content)
{
    char *dup = my_strdup("hello");

    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "hello");
    free(dup);
}

Test(my_strconcat, concatenates_strings)
{
    char *joined = my_strconcat("mini", "shell");

    cr_assert_not_null(joined);
    cr_assert_str_eq(joined, "minishell");
    free(joined);
}

Test(my_strstr, finds_substring)
{
    const char *res = my_strstr("hello world", "world");

    cr_assert_not_null(res);
    cr_assert_str_eq(res, "world");
}

Test(my_str_to_word_array, splits_words)
{
    char **arr = my_str_to_word_array("ls -la /tmp", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "ls");
    cr_assert_str_eq(arr[1], "-la");
    cr_assert_str_eq(arr[2], "/tmp");
    cr_assert_null(arr[3]);
    free_array(arr);
}

Test(my_wordarray_len, counts_elements)
{
    char *arr[] = {"a", "b", NULL};

    cr_assert_eq(my_wordarray_len(arr), 2);
}

