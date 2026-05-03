/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_which_where
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"

static main_t *make_stock(void)
{
    main_t *stock = calloc(1, sizeof(main_t));
    char *src[] = {"/bin", "/usr/bin", NULL};

    cr_assert_not_null(stock);
    stock->path = malloc(sizeof(char *) * 3);
    cr_assert_not_null(stock->path);
    stock->path[0] = my_strdup(src[0]);
    stock->path[1] = my_strdup(src[1]);
    stock->path[2] = NULL;
    return stock;
}

static void free_stock(main_t *stock)
{
    free_array(stock->path);
    free(stock);
}
Test(builtin_which, shell_builtin_prints_message, .init = cr_redirect_stdout)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {"cd", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_which(stock, &ctx), 0);
    fflush(stdout);
    cr_assert_stdout_eq_str("cd: shell built-in command.\n");
    free_stock(stock);
}

Test(builtin_which, finds_external_binary, .init = cr_redirect_stdout)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {"true", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_which(stock, &ctx), 0);
    fflush(stdout);
    cr_assert_stdout_eq_str("/bin/true\n");
    free_stock(stock);
}

Test(builtin_which, returns_error_for_unknown_binary, .init = cr_redirect_stderr)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {"__42sh_no_binary__", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_which(stock, &ctx), 1);
    free_stock(stock);
}

Test(builtin_which, no_args_returns_error, .init = cr_redirect_stderr)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_which(stock, &ctx), 1);
    fflush(stderr);
    cr_assert_stderr_eq_str("which: Too few arguments.\n");
    free_stock(stock);
}

Test(builtin_which, which_is_a_builtin, .init = cr_redirect_stdout)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {"which", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_which(stock, &ctx), 0);
    fflush(stdout);
    cr_assert_stdout_eq_str("which: shell built-in command.\n");
    free_stock(stock);
}
Test(builtin_where, shell_builtin_prints_message, .init = cr_redirect_stdout)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {"cd", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_where(stock, &ctx), 0);
    fflush(stdout);
    cr_assert_stdout_eq_str("cd is a shell built-in\n");
    free_stock(stock);
}

Test(builtin_where, external_binary_returns_success, .init = cr_redirect_stdout)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {"true", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_where(stock, &ctx), 0);
    free_stock(stock);
}

Test(builtin_where, returns_error_for_unknown_binary, .init = cr_redirect_stderr)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {"__42sh_no_binary__", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_where(stock, &ctx), 1);
    fflush(stderr);
    cr_assert_stderr_eq_str("__42sh_no_binary__: Command not found.\n");
    free_stock(stock);
}

Test(builtin_where, no_args_returns_error, .init = cr_redirect_stderr)
{
    main_t *stock = make_stock();
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_where(stock, &ctx), 1);
    fflush(stderr);
    cr_assert_stderr_eq_str("where: Too few arguments.\n");
    free_stock(stock);
}
