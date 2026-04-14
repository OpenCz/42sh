/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** unit tests
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdlib.h>
#include "c_zsh.h"

static void free_env_list_local(env_t *env)
{
    env_t *next = NULL;

    while (env) {
        next = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = next;
    }
}

Test(my_strlen, empty_string_returns_zero)
{
    cr_assert_eq(my_strlen(""), 0);
}

Test(my_strlen, one_char_returns_one)
{
    cr_assert_eq(my_strlen("a"), 1);
}

Test(my_strlen, normal_word_length)
{
    cr_assert_eq(my_strlen("minishell"), 9);
}

Test(my_strlen, string_with_spaces)
{
    cr_assert_eq(my_strlen("a b c"), 5);
}

Test(my_strlen, digits_and_symbols)
{
    cr_assert_eq(my_strlen("42!"), 3);
}

Test(my_strlen, long_string)
{
    cr_assert_eq(my_strlen("abcdefghijklmnopqrstuvwxyz"), 26);
}

Test(my_strcmp, equal_strings)
{
    cr_assert_eq(my_strcmp("abc", "abc"), 0);
}

Test(my_strcmp, first_lower_than_second)
{
    cr_assert_lt(my_strcmp("abc", "abd"), 0);
}

Test(my_strcmp, first_greater_than_second)
{
    cr_assert_gt(my_strcmp("abd", "abc"), 0);
}

Test(my_strcmp, prefix_is_smaller)
{
    cr_assert_lt(my_strcmp("ab", "abc"), 0);
}

Test(my_strcmp, longer_is_greater_when_prefix_matches)
{
    cr_assert_gt(my_strcmp("abc", "ab"), 0);
}

Test(my_strcmp, null_first_returns_minus_one)
{
    cr_assert_eq(my_strcmp(NULL, "abc"), -1);
}

Test(my_strcmp, null_second_returns_minus_one)
{
    cr_assert_eq(my_strcmp("abc", NULL), -1);
}

Test(my_strcmp, both_null_returns_minus_one)
{
    cr_assert_eq(my_strcmp(NULL, NULL), -1);
}

Test(my_strncmp, equal_with_n_exact)
{
    cr_assert_eq(my_strncmp("abcdef", "abcxyz", 3), 0);
}

Test(my_strncmp, different_before_n)
{
    cr_assert_lt(my_strncmp("abx", "aby", 3), 0);
}

Test(my_strncmp, different_before_n_reverse)
{
    cr_assert_gt(my_strncmp("aby", "abx", 3), 0);
}

Test(my_strncmp, n_one_compares_first_char_only)
{
    cr_assert_eq(my_strncmp("abc", "axz", 1), 0);
}

Test(my_strncmp, full_equal)
{
    cr_assert_eq(my_strncmp("hello", "hello", 5), 0);
}

Test(my_strncmp, prefix_equal_shorter_left)
{
    cr_assert_lt(my_strncmp("ab", "abc", 3), 0);
}

Test(my_strncmp, prefix_equal_shorter_right)
{
    cr_assert_gt(my_strncmp("abc", "ab", 3), 0);
}

Test(my_strncmp, zero_n_returns_difference_on_first_char)
{
    cr_assert_eq(my_strncmp("a", "a", 0), 0);
}

Test(my_strdup, duplicate_basic_string)
{
    char *dup = my_strdup("hello");

    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "hello");
    free(dup);
}

Test(my_strdup, duplicate_empty_string)
{
    char *dup = my_strdup("");

    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "");
    free(dup);
}

Test(my_strdup, duplicate_keeps_content)
{
    char *dup = my_strdup("abc def");

    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "abc def");
    free(dup);
}

Test(my_strdup, duplicate_returns_distinct_pointer)
{
    char src[] = "pointer";
    char *dup = my_strdup(src);

    cr_assert_not_null(dup);
    cr_assert_neq(dup, src);
    free(dup);
}

Test(my_strdup, duplicate_numeric_string)
{
    char *dup = my_strdup("12345");

    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "12345");
    free(dup);
}

Test(my_strconcat, concat_two_words)
{
    char *joined = my_strconcat("mini", "shell");

    cr_assert_not_null(joined);
    cr_assert_str_eq(joined, "minishell");
    free(joined);
}

Test(my_strconcat, concat_with_empty_left)
{
    char *joined = my_strconcat("", "right");

    cr_assert_not_null(joined);
    cr_assert_str_eq(joined, "right");
    free(joined);
}

Test(my_strconcat, concat_with_empty_right)
{
    char *joined = my_strconcat("left", "");

    cr_assert_not_null(joined);
    cr_assert_str_eq(joined, "left");
    free(joined);
}

Test(my_strconcat, concat_two_empty_strings)
{
    char *joined = my_strconcat("", "");

    cr_assert_not_null(joined);
    cr_assert_str_eq(joined, "");
    free(joined);
}

Test(my_strconcat, concat_with_symbols)
{
    char *joined = my_strconcat("/usr", "/bin");

    cr_assert_not_null(joined);
    cr_assert_str_eq(joined, "/usr/bin");
    free(joined);
}

Test(my_wordarray_len, two_elements)
{
    char *arr[] = {"a", "b", NULL};

    cr_assert_eq(my_wordarray_len(arr), 2);
}

Test(my_wordarray_len, single_element)
{
    char *arr[] = {"only", NULL};

    cr_assert_eq(my_wordarray_len(arr), 1);
}

Test(my_wordarray_len, no_element)
{
    char *arr[] = {NULL};

    cr_assert_eq(my_wordarray_len(arr), 0);
}

Test(my_wordarray_len, many_elements)
{
    char *arr[] = {"1", "2", "3", "4", NULL};

    cr_assert_eq(my_wordarray_len(arr), 4);
}

Test(my_char_isnum, starts_with_digit)
{
    cr_assert_eq(my_char_isnum("1abc"), 1);
}

Test(my_char_isnum, starts_with_letter)
{
    cr_assert_eq(my_char_isnum("a1bc"), 0);
}

Test(my_char_isnum, starts_with_symbol)
{
    cr_assert_eq(my_char_isnum("_abc"), 0);
}

Test(my_char_isnum, empty_string)
{
    cr_assert_eq(my_char_isnum(""), 0);
}

Test(my_str_is_alphanum, letters_only_is_valid)
{
    cr_assert_eq(my_str_is_alphanum("Alpha"), 0);
}

Test(my_str_is_alphanum, digits_only_is_valid)
{
    cr_assert_eq(my_str_is_alphanum("12345"), 0);
}

Test(my_str_is_alphanum, mixed_is_valid)
{
    cr_assert_eq(my_str_is_alphanum("A1b2C3"), 0);
}

Test(my_str_is_alphanum, underscore_is_invalid)
{
    cr_assert_eq(my_str_is_alphanum("A_B"), 1);
}

Test(my_str_is_alphanum, symbol_is_invalid)
{
    cr_assert_eq(my_str_is_alphanum("ABC!"), 1);
}

Test(my_strstr, find_simple_substring)
{
    const char *res = my_strstr("hello world", "world");

    cr_assert_not_null(res);
    cr_assert_str_eq(res, "world");
}

Test(my_strstr, find_substring_at_start)
{
    const char *res = my_strstr("abcdef", "abc");

    cr_assert_not_null(res);
    cr_assert_str_eq(res, "abcdef");
}

Test(my_strstr, find_substring_at_end)
{
    const char *res = my_strstr("abcdef", "def");

    cr_assert_not_null(res);
    cr_assert_str_eq(res, "def");
}

Test(my_strstr, not_found_returns_null)
{
    cr_assert_null(my_strstr("abcdef", "xyz"));
}

Test(my_strstr, empty_pattern_returns_original)
{
    const char *src = "abc";

    cr_assert_eq(my_strstr(src, ""), src);
}

Test(my_strstr, single_char_pattern)
{
    const char *res = my_strstr("abc", "b");

    cr_assert_not_null(res);
    cr_assert_str_eq(res, "bc");
}

Test(my_strstr, repeated_pattern)
{
    const char *res = my_strstr("aaaaab", "aaab");

    cr_assert_not_null(res);
    cr_assert_str_eq(res, "aaab");
}

Test(get_redirection, detect_double_out_first)
{
    cr_assert_str_eq(get_redirection("echo hi >> out.txt"), ">>");
}

Test(get_redirection, detect_double_in)
{
    cr_assert_str_eq(get_redirection("cat << EOF"), "<<");
}

Test(get_redirection, detect_simple_out)
{
    cr_assert_str_eq(get_redirection("echo hi > out.txt"), ">");
}

Test(get_redirection, detect_simple_in)
{
    cr_assert_str_eq(get_redirection("cat < in.txt"), "<");
}

Test(get_redirection, no_redirection_returns_null)
{
    cr_assert_null(get_redirection("echo hi"));
}

Test(get_redirection, prefer_double_when_both_symbols_exist)
{
    cr_assert_str_eq(get_redirection("echo >>file"), ">>");
}

Test(my_str_to_word_array, split_by_space)
{
    char **arr = my_str_to_word_array("ls -la /tmp", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "ls");
    cr_assert_str_eq(arr[1], "-la");
    cr_assert_str_eq(arr[2], "/tmp");
    cr_assert_null(arr[3]);
    free_array(arr);
}

Test(my_str_to_word_array, collapse_multiple_separators)
{
    char **arr = my_str_to_word_array("a   b", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "a");
    cr_assert_str_eq(arr[1], "b");
    cr_assert_null(arr[2]);
    free_array(arr);
}

Test(my_str_to_word_array, leading_separator)
{
    char **arr = my_str_to_word_array("   abc", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "abc");
    cr_assert_null(arr[1]);
    free_array(arr);
}

Test(my_str_to_word_array, trailing_separator)
{
    char **arr = my_str_to_word_array("abc   ", " ");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "abc");
    cr_assert_null(arr[1]);
    free_array(arr);
}

Test(my_str_to_word_array, custom_separator_chars)
{
    char **arr = my_str_to_word_array("PATH=/bin:/usr/bin", "=:");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "PATH");
    cr_assert_str_eq(arr[1], "/bin");
    cr_assert_str_eq(arr[2], "/usr/bin");
    cr_assert_null(arr[3]);
    free_array(arr);
}

Test(my_str_to_word_array, empty_input_gives_empty_array)
{
    char **arr = my_str_to_word_array("", " ");

    cr_assert_not_null(arr);
    cr_assert_null(arr[0]);
    free_array(arr);
}

Test(my_str_to_word_array, null_input_returns_null)
{
    cr_assert_null(my_str_to_word_array(NULL, " "));
}

Test(env_access, init_env_then_get_path_and_home)
{
    char *envp[] = {"HOME=/home/student", "PATH=/bin:/usr/bin", "TERM=xterm", NULL};
    env_t *env = init_env(envp);

    cr_assert_not_null(env);
    cr_assert_str_eq(get_home(env), "/home/student");
    cr_assert_str_eq(get_path(env), "/bin:/usr/bin");
    free_env_list_local(env);
}

Test(env_access, unsetenv_removes_matching_node)
{
    char *envp[] = {"HOME=/home/student", "PATH=/bin:/usr/bin", "TERM=xterm", NULL};
    main_t shell = {0};

    shell.stock_env = init_env(envp);
    cr_assert_not_null(shell.stock_env);

    {
        char *args[] = {"PATH", NULL};
        shell.arg_command = args;
        cr_assert_eq(my_unsetenv(&shell), 0);
    }

    cr_assert_null(get_path(shell.stock_env));
    cr_assert_not_null(get_home(shell.stock_env));
    free_env_list_local(shell.stock_env);
}
