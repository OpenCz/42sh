/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_core_init
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

static alias_stock_t *find_alias(alias_stock_t *head, const char *name)
{
    for (; head; head = head->next)
        if (my_strcmp(head->new_name, (char *)name) == 0)
            return head;
    return NULL;
}

static void free_aliases(alias_stock_t *head)
{
    alias_stock_t *next;

    while (head) {
        next = head->next;
        free(head->new_name);
        free(head->command);
        free(head);
        head = next;
    }
}

Test(init_env, injects_default_path_when_missing)
{
    char *env[] = {
        "HOME=/home/erwan",
        NULL
    };
    env_t *stock = init_env(env);

    cr_assert_not_null(stock);
    cr_assert_str_eq(stock->key, "PATH");
    cr_assert_str_eq(stock->value, "/bin:/usr/bin");
    cr_assert_not_null(stock->next);
    cr_assert_str_eq(stock->next->key, "HOME");
    cr_assert_str_eq(stock->next->value, "/home/erwan");
    cr_assert_null(stock->next->next);
    free_linked_list(stock);
}

Test(init_env, keeps_existing_path_and_null_values)
{
    char *env[] = {
        "PATH=/custom/bin",
        "FOO",
        NULL
    };
    env_t *stock = init_env(env);

    cr_assert_not_null(stock);
    cr_assert_str_eq(stock->key, "PATH");
    cr_assert_str_eq(stock->value, "/custom/bin");
    cr_assert_not_null(stock->next);
    cr_assert_str_eq(stock->next->key, "FOO");
    cr_assert_null(stock->next->value);
    cr_assert_null(stock->next->next);
    free_linked_list(stock);
}

Test(init_main, initializes_fields_from_env)
{
    char *env[] = {
        "HOME=/home/erwan",
        "PATH=/usr/local/bin:/bin",
        NULL
    };
    main_t *stock = init_main(env);

    cr_assert_not_null(stock);
    cr_assert_not_null(stock->stock_env);
    cr_assert_str_eq(stock->stock_env->key, "HOME");
    cr_assert_str_eq(stock->stock_env->value, "/home/erwan");
    cr_assert_not_null(stock->stock_env->next);
    cr_assert_str_eq(stock->stock_env->next->key, "PATH");
    cr_assert_str_eq(stock->stock_env->next->value, "/usr/local/bin:/bin");
    cr_assert_str_eq(stock->path[0], "/usr/local/bin");
    cr_assert_str_eq(stock->path[1], "/bin");
    cr_assert_null(stock->path[2]);
    cr_assert_str_eq(stock->home, "/home/erwan");
    cr_assert_null(stock->command);
    cr_assert_null(stock->argv);
    cr_assert_null(stock->arg_command);
    cr_assert_null(stock->redirection);
    cr_assert_null(stock->old_path);
    free_main(stock);
}

Test(update_rc, keeps_last_duplicate_alias_definition)
{
    char path[] = "/tmp/42sh_rc_XXXXXX";
    const char *content = "[alias]\nfoo = echo first\nfoo = echo second\n";
    czshrc_t *rc = NULL;
    int fd = mkstemp(path);

    cr_assert(fd >= 0);
    cr_assert_eq(write(fd, content, strlen(content)), (ssize_t)strlen(content));
    close(fd);
    rc = update_rc(path);
    unlink(path);
    cr_assert_not_null(rc);
    cr_assert_not_null(rc->aliases);
    cr_assert_not_null(find_alias(rc->aliases, "foo"));
    cr_assert_str_eq(find_alias(rc->aliases, "foo")->command, "echo second");
    cr_assert_null(find_alias(rc->aliases, "foo")->next);
    free_aliases(rc->aliases);
    free_alloc(rc->prompt);
    free(rc);
}

