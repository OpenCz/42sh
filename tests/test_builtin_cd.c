/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_cd
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "c_zsh.h"

int my_chdir_call(char *path);

static env_t *node_new(const char *key, const char *value)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = my_strdup((char *)key);
    node->value = value ? my_strdup((char *)value) : NULL;
    node->next = NULL;
    return node;
}

static env_t *find_key(env_t *env, const char *key)
{
    for (; env; env = env->next)
        if (my_strcmp(env->key, (char *)key) == 0)
            return env;
    return NULL;
}

static char *create_temp_dir(void)
{
    char template[] = "/tmp/42sh_cd_covXXXXXX";
    char *dir = mkdtemp(template);

    cr_assert_not_null(dir);
    return my_strdup(dir);
}

static char *create_temp_file(void)
{
    char template[] = "/tmp/42sh_cd_fileXXXXXX";
    int fd = mkstemp(template);

    cr_assert(fd != -1);
    close(fd);
    return my_strdup(template);
}

Test(builtin_cd, returns_error_when_directory_does_not_exist)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"/tmp/42sh_this_path_should_not_exist", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_cd(&stock, &ctx), 1);
}

Test(builtin_cd, tilde_uses_home_and_updates_pwd_oldpwd)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"~", NULL};
    char template[] = "/tmp/42sh_cd_testXXXXXX";
    char *tmpdir = mkdtemp(template);
    char *old_cwd = getcwd(NULL, 0);
    char *new_cwd = NULL;
    env_t *pwd;
    env_t *oldpwd;

    cr_assert_not_null(tmpdir);
    cr_assert_not_null(old_cwd);
    stock.stock_env = node_new("PWD", "/unused");
    stock.stock_env->next = node_new("OLDPWD", "/unused_old");
    stock.home = tmpdir;
    ctx.arg_command = args;
    cr_assert_eq(builtin_cd(&stock, &ctx), SUCCESS);
    new_cwd = getcwd(NULL, 0);
    cr_assert_not_null(new_cwd);
    cr_assert_str_eq(new_cwd, tmpdir);
    cr_assert_str_eq(stock.old_path, old_cwd);
    pwd = find_key(stock.stock_env, "PWD");
    oldpwd = find_key(stock.stock_env, "OLDPWD");
    cr_assert_not_null(pwd);
    cr_assert_not_null(oldpwd);
    cr_assert_str_eq(pwd->value, tmpdir);
    cr_assert_str_eq(oldpwd->value, old_cwd);
    cr_assert_eq(chdir(old_cwd), 0);
    cr_assert_eq(rmdir(tmpdir), 0);
    free(new_cwd);
    free(old_cwd);
    free(stock.old_path);
    free_linked_list(stock.stock_env);
}

Test(builtin_cd, uses_home_when_argument_is_missing)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};
    char *old_cwd = getcwd(NULL, 0);
    char *tmpdir = create_temp_dir();

    cr_assert_not_null(old_cwd);
    stock.home = tmpdir;
    stock.stock_env = node_new("PWD", "/unused");
    stock.stock_env->next = node_new("OLDPWD", "/unused_old");
    ctx.arg_command = args;
    cr_assert_eq(builtin_cd(&stock, &ctx), SUCCESS);
    cr_assert_eq(chdir(old_cwd), 0);
    cr_assert_eq(rmdir(tmpdir), 0);
    free(old_cwd);
    free(tmpdir);
    free(stock.old_path);
    free_linked_list(stock.stock_env);
}

Test(builtin_cd, rejects_dash_when_old_path_is_missing)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"-", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_cd(&stock, &ctx), 1);
}

Test(builtin_cd, rejects_regular_file_path)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};
    char *file = create_temp_file();

    args[0] = file;
    ctx.arg_command = args;
    cr_assert_eq(builtin_cd(&stock, &ctx), 1);
    unlink(file);
    free(file);
}

Test(my_chdir, wrapper_uses_main_arguments)
{
    main_t stock = {0};
    char *args[] = {"~", NULL};
    char *tmpdir = create_temp_dir();
    char *old_cwd = getcwd(NULL, 0);

    cr_assert_not_null(old_cwd);
    stock.arg_command = args;
    stock.home = tmpdir;
    stock.stock_env = node_new("PWD", "/unused");
    stock.stock_env->next = node_new("OLDPWD", "/unused_old");
    cr_assert_eq(my_chdir(&stock), SUCCESS);
    cr_assert_eq(chdir(old_cwd), 0);
    cr_assert_eq(rmdir(tmpdir), 0);
    free(old_cwd);
    free(tmpdir);
    free(stock.old_path);
    free_linked_list(stock.stock_env);
}

Test(my_chdir_call, fails_on_regular_file)
{
    char *file = create_temp_file();

    cr_assert_eq(my_chdir_call(file), 1);
    unlink(file);
    free(file);
}

