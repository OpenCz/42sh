/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_limit
** Covers: get_good_limit, builtin_limit, builtin_unlimit, verif_time
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/resource.h>
#include "../include/c_zsh.h"
Test(get_good_limit, full_name_cputime_returns_limit)
{
    limit_t *lim = get_good_limit("cputime");

    cr_assert_not_null(lim);
    cr_assert_str_eq(lim->good_name, "cputime");
    cr_assert_eq(lim->good_lim, RLIMIT_CPU);
    free(lim);
}

Test(get_good_limit, prefix_cp_resolves_cputime)
{
    limit_t *lim = get_good_limit("cp");

    cr_assert_not_null(lim);
    cr_assert_str_eq(lim->good_name, "cputime");
    free(lim);
}

Test(get_good_limit, prefix_fi_resolves_filesize)
{
    limit_t *lim = get_good_limit("fi");

    cr_assert_not_null(lim);
    cr_assert_str_eq(lim->good_name, "filesize");
    free(lim);
}

Test(get_good_limit, prefix_st_resolves_stacksize)
{
    limit_t *lim = get_good_limit("st");

    cr_assert_not_null(lim);
    cr_assert_str_eq(lim->good_name, "stacksize");
    free(lim);
}

Test(get_good_limit, ambiguous_prefix_returns_null, .init = cr_redirect_stdout)
{
    limit_t *lim = get_good_limit("ma");

    cr_assert_null(lim);
}

Test(get_good_limit, unknown_name_returns_null, .init = cr_redirect_stdout)
{
    limit_t *lim = get_good_limit("zzz");

    cr_assert_null(lim);
}

Test(get_good_limit, full_name_descriptors)
{
    limit_t *lim = get_good_limit("descriptors");

    cr_assert_not_null(lim);
    cr_assert_str_eq(lim->good_name, "descriptors");
    cr_assert_eq(lim->good_lim, RLIMIT_NOFILE);
    free(lim);
}

Test(get_good_limit, full_name_stacksize)
{
    limit_t *lim = get_good_limit("stacksize");

    cr_assert_not_null(lim);
    cr_assert_str_eq(lim->good_name, "stacksize");
    cr_assert_eq(lim->good_lim, RLIMIT_STACK);
    free(lim);
}
Test(verif_time, cputime_seconds_only, .init = cr_redirect_stdout)
{
    struct rlimit rl = {.rlim_cur = 5};

    verif_time("cputime", &rl);
    fflush(stdout);
    cr_assert_stdout_eq_str("0:05");
}

Test(verif_time, cputime_minutes_and_seconds, .init = cr_redirect_stdout)
{
    struct rlimit rl = {.rlim_cur = 65};

    verif_time("cputime", &rl);
    fflush(stdout);
    cr_assert_stdout_eq_str("1:05");
}

Test(verif_time, cputime_hours_minutes_seconds, .init = cr_redirect_stdout)
{
    struct rlimit rl = {.rlim_cur = 3661};

    verif_time("cputime", &rl);
    fflush(stdout);
    cr_assert_stdout_eq_str("1:01:01");
}

Test(verif_time, cputime_round_hours, .init = cr_redirect_stdout)
{
    struct rlimit rl = {.rlim_cur = 7200};

    verif_time("cputime", &rl);
    fflush(stdout);
    cr_assert_stdout_eq_str("2:00:00");
}

Test(verif_time, non_cputime_prints_raw_value, .init = cr_redirect_stdout)
{
    struct rlimit rl = {.rlim_cur = 42};

    verif_time("stacksize", &rl);
    fflush(stdout);
    cr_assert_stdout_eq_str("42");
}

Test(verif_time, non_cputime_descriptors, .init = cr_redirect_stdout)
{
    struct rlimit rl = {.rlim_cur = 1024};

    verif_time("descriptors", &rl);
    fflush(stdout);
    cr_assert_stdout_eq_str("1024");
}
Test(builtin_limit, no_args_displays_all_limits, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_limit(&stock, &ctx), SUCCESS);
}

Test(builtin_limit, unknown_name_returns_error, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"zzznolimit", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_limit(&stock, &ctx), 1);
}

Test(builtin_limit, too_many_args_returns_error, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"cputime", "100", "extra", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_limit(&stock, &ctx), 1);
}

Test(builtin_limit, query_single_known_limit, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"cputime", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_limit(&stock, &ctx), SUCCESS);
}

Test(builtin_limit, query_descriptors, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"descriptors", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_limit(&stock, &ctx), SUCCESS);
}
Test(builtin_unlimit, too_many_args_returns_error, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"cputime", "extra", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_unlimit(&stock, &ctx), 1);
}

Test(builtin_unlimit, unknown_limit_returns_error, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"zzznolimit", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_unlimit(&stock, &ctx), 1);
}

Test(builtin_unlimit, single_known_limit_does_not_crash, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"descriptors", NULL};

    ctx.arg_command = args;
    builtin_unlimit(&stock, &ctx);
}
