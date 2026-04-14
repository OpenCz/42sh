/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_apply_redirection
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/42sh.h"

static char *create_temp_file(const char *content)
{
    char template[] = "/tmp/42sh_redir_XXXXXX";
    int fd = mkstemp(template);
    char *path;

    cr_assert(fd != -1);
    cr_assert_geq(write(fd, content, my_strlen((char *)content)), 0);
    close(fd);
    path = my_strdup(template);
    cr_assert_not_null(path);
    return path;
}

static void read_file_into_buffer(const char *path, char *buffer)
{
    int fd = open(path, O_RDONLY);
    ssize_t len;

    cr_assert(fd != -1);
    len = read(fd, buffer, 63);
    cr_assert_geq(len, 0);
    buffer[len] = '\0';
    close(fd);
}

Test(apply_redirection, returns_success_when_absent)
{
    command_ctx_t ctx = {0};

    cr_assert_eq(apply_redirection(&ctx), SUCCESS);
}

Test(apply_redirection, rejects_missing_target)
{
    command_ctx_t ctx = {0};
    char *argv[] = {"echo", ">", NULL};

    cr_redirect_stderr();
    ctx.argv = argv;
    ctx.redirection = ">";
    cr_assert_eq(apply_redirection(&ctx), 1);
    fflush(stderr);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}

Test(apply_redirection, truncates_stdout_target)
{
    command_ctx_t ctx = {0};
    char *path = create_temp_file("old content");
    char *argv[] = {"echo", ">", path, NULL};
    int saved_stdout = dup(STDOUT_FILENO);
    char buffer[64];

    cr_assert(saved_stdout != -1);
    ctx.argv = argv;
    ctx.redirection = ">";
    cr_assert_eq(apply_redirection(&ctx), SUCCESS);
    cr_assert_null(ctx.argv[1]);
    cr_assert_geq(write(STDOUT_FILENO, "new", 3), 0);
    cr_assert_eq(dup2(saved_stdout, STDOUT_FILENO), STDOUT_FILENO);
    close(saved_stdout);
    read_file_into_buffer(path, buffer);
    cr_assert_str_eq(buffer, "new");
    unlink(path);
    free(path);
}

Test(apply_redirection, appends_stdout_target)
{
    command_ctx_t ctx = {0};
    char *path = create_temp_file("old");
    char *argv[] = {"echo", ">>", path, NULL};
    int saved_stdout = dup(STDOUT_FILENO);
    char buffer[64];

    cr_assert(saved_stdout != -1);
    ctx.argv = argv;
    ctx.redirection = ">>";
    cr_assert_eq(apply_redirection(&ctx), SUCCESS);
    cr_assert_null(ctx.argv[1]);
    cr_assert_geq(write(STDOUT_FILENO, "new", 3), 0);
    cr_assert_eq(dup2(saved_stdout, STDOUT_FILENO), STDOUT_FILENO);
    close(saved_stdout);
    read_file_into_buffer(path, buffer);
    cr_assert_str_eq(buffer, "oldnew");
    unlink(path);
    free(path);
}

Test(apply_redirection, redirects_stdin_from_file)
{
    command_ctx_t ctx = {0};
    char *path = create_temp_file("input data");
    char *argv[] = {"cat", "<", path, NULL};
    int saved_stdin = dup(STDIN_FILENO);
    char buffer[64];
    ssize_t len;

    cr_assert(saved_stdin != -1);
    ctx.argv = argv;
    ctx.redirection = "<";
    cr_assert_eq(apply_redirection(&ctx), SUCCESS);
    cr_assert_null(ctx.argv[1]);
    len = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    cr_assert_geq(len, 0);
    buffer[len] = '\0';
    cr_assert_str_eq(buffer, "input data");
    cr_assert_eq(dup2(saved_stdin, STDIN_FILENO), STDIN_FILENO);
    close(saved_stdin);
    unlink(path);
    free(path);
}

Test(apply_redirection, heredoc_reads_until_delimiter)
{
    command_ctx_t ctx = {0};
    char *source = create_temp_file("first line\nEOF\n");
    char *argv[] = {"cat", "<<", "EOF", NULL};
    int saved_stdin = dup(STDIN_FILENO);
    int source_fd;
    char buffer[64];
    ssize_t len;

    cr_assert(saved_stdin != -1);
    source_fd = open(source, O_RDONLY);
    cr_assert(source_fd != -1);
    cr_assert_eq(dup2(source_fd, STDIN_FILENO), STDIN_FILENO);
    close(source_fd);
    ctx.argv = argv;
    ctx.redirection = "<<";
    cr_assert_eq(apply_redirection(&ctx), SUCCESS);
    cr_assert_null(ctx.argv[1]);
    len = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    cr_assert_geq(len, 0);
    buffer[len] = '\0';
    cr_assert_str_eq(buffer, "first line\n");
    cr_assert_eq(dup2(saved_stdin, STDIN_FILENO), STDIN_FILENO);
    close(saved_stdin);
    unlink(source);
    free(source);
}

