/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_exec_error_case
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/c_zsh.h"

static char *create_temp_file(const char *content, mode_t mode)
{
    char template[] = "/tmp/42sh_exec_errXXXXXX";
    int fd = mkstemp(template);
    char *path;

    cr_assert(fd != -1);
    cr_assert_eq(write(fd, content, my_strlen((char *)content)), (ssize_t)my_strlen((char *)content));
    cr_assert_eq(fchmod(fd, mode), 0);
    close(fd);
    path = my_strdup(template);
    cr_assert_not_null(path);
    return path;
}

static int status_from_signal(int sig, int with_core)
{
    return sig | (with_core ? 0x80 : 0);
}

Test(child_exec, returns_126_for_enoexec)
{
    command_ctx_t ctx = {0};
    char *argv[] = {"broken", NULL};
    char *env[] = {NULL};
    char *path = create_temp_file("not a binary\n", 0755);

    cr_redirect_stderr();
    ctx.command = "broken";
    ctx.argv = argv;
    cr_assert_eq(child_exec(&ctx, path, env), 126);
    unlink(path);
    free(path);
}

Test(child_exec, returns_126_for_eacces)
{
    command_ctx_t ctx = {0};
    char *argv[] = {"noexec", NULL};
    char *env[] = {NULL};
    char *path = create_temp_file("echo hi\n", 0644);

    cr_redirect_stderr();
    ctx.command = "noexec";
    ctx.argv = argv;
    cr_assert_eq(child_exec(&ctx, path, env), 126);
    unlink(path);
    free(path);
}

Test(get_seg, handles_exit_signal_and_core_dump)
{
    cr_assert_eq(get_seg(W_EXITCODE(0, 0)), 0);
    cr_assert_eq(get_seg(status_from_signal(SIGFPE, 0)), 136);
    cr_assert_eq(get_seg(status_from_signal(SIGSEGV, 1)), 139);
}

