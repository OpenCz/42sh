/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_jobs
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

Test(builtin_jobs, returns_success)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};

    cr_assert_eq(builtin_jobs(&stock, &ctx), SUCCESS);
}

Test(builtin_foreground, returns_success)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};

    cr_assert_eq(builtin_foreground(&stock, &ctx), SUCCESS);
}

Test(builtin_background, returns_success)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};

    cr_assert_eq(builtin_background(&stock, &ctx), SUCCESS);
}

