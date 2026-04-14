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

