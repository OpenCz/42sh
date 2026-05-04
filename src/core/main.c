/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Shell entry point: main() calls init_main, setup_shell_signals,
** run_shell_loop; serialize() trims trailing newline; the loop
** calls get_command then execute_command until 'exit' or EOF.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/
#include "../../include/c_zsh.h"

static char *serialize(char *buffer)
{
    size_t start = 0;
    size_t end = 0;

    if (!buffer)
        return NULL;
    end = my_strlen(buffer);
    while (end > 0 && isspace((unsigned char)buffer[end - 1]))
        end--;
    buffer[end] = '\0';
    while (buffer[start] != '\0' && isspace((unsigned char)buffer[start]))
        start++;
    if (start > 0)
        memmove(buffer, buffer + start, end - start + 1);
    return buffer;
}

static bool handle_command_result(main_t *stock, loop_state_t *state,
    int *force)
{
    state->buffer = serialize(state->buffer);
    if (my_strcmp(state->buffer, "exit") == 0)
        return true;
    if (state->cmd == -1) {
        *force = (*force >= -1 && *force <= 0) ? *force + 1 : *force;
        return true;
    }
    state->last_exit = execute_command(stock, state->buffer);
    if (*force == 0)
        *force = -1;
    if (state->last_exit == 130) {
        display_prompt(stock->czshrc->prompt, get_user(stock->stock_env));
        state->prompt_displayed = true;
    } else {
        state->prompt_displayed = false;
    }
    return false;
}

static void free_var_local(env_t **local_var)
{
    env_t *tmp = NULL;

    while (*local_var) {
        tmp = *local_var;
        *local_var = (*local_var)->next;
        free_alloc(tmp->key);
        free_alloc(tmp->value);
        free_alloc(tmp);
    }
}

static void set_shell_prompt(loop_state_t *state, main_t *stock, int *force)
{
    if (!state->prompt_displayed)
        write_print(stock);
    state->prompt_displayed = true;
    state->cmd = get_command(stock, &state->buffer, stock->history,
        get_user(stock->stock_env));
}

static int suspend_jobs(job_controler_t *controler, int *force, main_t *stock)
{
    job_controler_t *tmp = controler->next;

    if (controler->next != NULL && (*force == 0)) {
        printf("^D\nThere are suspended jobs.\n");
        display_prompt(stock->czshrc->prompt, get_user(stock->stock_env));
        (*force) = 0;
        return 1;
    }
    if (*force)
        for (; tmp && tmp->next; tmp = tmp->next)
            kill(SIGKILL, tmp->job->pid);
    return 0;
}

static void loop_shell(main_t *stock, loop_state_t *state, int *force)
{
    while (my_strcmp(state->buffer, "exit") != 0) {
        handle_limit_signals(stock->signal->sfd, stock->signal);
        set_shell_prompt(state, stock, force);
        if (check_limit_signals(stock->signal))
            break;
        if (state->cmd == CONTINUE) {
            state->prompt_displayed = false;
            continue;
        }
        if (handle_command_result(stock, state, force))
            break;
        free_alloc(stock->last_exit);
        stock->last_exit = my_itoa(state->last_exit);
    }
    if (suspend_jobs(stock->controler, force, stock))
        loop_shell(stock, state, force);
}

static void run_shell_loop(main_t *stock, loop_state_t *state)
{
    int force = -1;

    stock->last_exit = my_itoa(state->last_exit);
    loop_shell(stock, state, &force);
    free_alloc(stock->last_exit);
    free_var_local(&stock->stock_local_var);
    write_tty("exit\n");
}

int main(int argc, char **argv, char **env)
{
    main_t *stock = init_main(env);
    loop_state_t state = {
        .buffer = NULL,
        .last_exit = 0,
        .cmd = 0,
        .prompt_displayed = false
    };

    (void)argc;
    (void)argv;
    setup_shell_signals(stock->signal);
    run_shell_loop(stock, &state);
    free_main(stock);
    return state.last_exit;
}
