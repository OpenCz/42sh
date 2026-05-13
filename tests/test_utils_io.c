/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_utils_io
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/c_zsh.h"

void my_putchar(char c, int sortie);

Test(my_putstr, writes_string_to_stdout, .init = cr_redirect_stdout)
{
    my_putstr("hello");
    fflush(stdout);
    cr_assert_stdout_eq_str("hello");
}

Test(my_putstr, handles_null_without_crash)
{
    my_putstr(NULL);
}

Test(my_putstrerror, writes_string_to_stderr)
{
    my_putstrerror("oops");
}

Test(my_putchar, writes_char_to_stdout, .init = cr_redirect_stdout)
{
    my_putchar('Z', STDOUT_FILENO);
    fflush(stdout);
    cr_assert_stdout_eq_str("Z");
}

Test(my_putnbr, prints_positive_integer, .init = cr_redirect_stdout)
{
    my_putnbr(42);
    fflush(stdout);
    cr_assert_stdout_eq_str("42");
}

Test(my_putnbr, prints_zero, .init = cr_redirect_stdout)
{
    my_putnbr(0);
    fflush(stdout);
    cr_assert_stdout_eq_str("0");
}

Test(my_putnbr, prints_negative_integer, .init = cr_redirect_stdout)
{
    my_putnbr(-3);
    fflush(stdout);
    cr_assert_stdout_eq_str("-3");
}

Test(my_putnbr, prints_multi_digit, .init = cr_redirect_stdout)
{
    my_putnbr(1234);
    fflush(stdout);
    cr_assert_stdout_eq_str("1234");
}

Test(get_file_size_stat, returns_exact_size_for_written_file)
{
    char template[] = "/tmp/42sh_sz_XXXXXX";
    int fd = mkstemp(template);

    cr_assert(fd != -1);
    cr_assert_eq(write(fd, "hello", 5), 5);
    close(fd);
    cr_assert_eq(get_file_size_stat(template), 5);
    unlink(template);
}

Test(get_file_size_stat, returns_zero_for_empty_file)
{
    char template[] = "/tmp/42sh_sz_empty_XXXXXX";
    int fd = mkstemp(template);

    cr_assert(fd != -1);
    close(fd);
    cr_assert_eq(get_file_size_stat(template), 0);
    unlink(template);
}

Test(get_file_size_stat, returns_minus_one_for_null_path, .init = cr_redirect_stderr)
{
    cr_assert_eq(get_file_size_stat(NULL), -1);
}

Test(get_file_size_stat, returns_minus_one_for_missing_file,
    .init = cr_redirect_stderr)
{
    cr_assert_eq(get_file_size_stat("/tmp/__42sh_no_such_file__"), -1);
}

Test(openator, reads_file_content)
{
    char template[] = "/tmp/42sh_open_XXXXXX";
    int fd = mkstemp(template);
    char *content;

    cr_assert(fd != -1);
    cr_assert_eq(write(fd, "world", 5), 5);
    close(fd);
    content = openator(template);
    cr_assert_not_null(content);
    cr_assert_str_eq(content, "world");
    free(content);
    unlink(template);
}

Test(openator, returns_null_for_null_path, .init = cr_redirect_stderr)
{
    cr_assert_null(openator(NULL));
}

Test(openator, returns_null_for_missing_file, .init = cr_redirect_stderr)
{
    cr_assert_null(openator("/tmp/__42sh_missing_file__"));
}

Test(openator, returns_null_for_empty_file, .init = cr_redirect_stderr)
{
    char template[] = "/tmp/42sh_open_empty_XXXXXX";
    int fd = mkstemp(template);

    cr_assert(fd != -1);
    close(fd);
    cr_assert_null(openator(template));
    unlink(template);
}
