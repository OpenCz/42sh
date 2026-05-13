/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_jobs
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

static job_controler_t *make_job_controler(void)
{
    job_controler_t *controler = calloc(1, sizeof(job_controler_t));

    cr_assert_not_null(controler);
    return controler;
}

Test(builtin_jobs, returns_success)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};

    stock.controler = make_job_controler();

    cr_assert_eq(builtin_jobs(&stock, &ctx), SUCCESS);
    free(stock.controler);
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

