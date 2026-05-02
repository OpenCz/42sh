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

static bool handle_command_result(main_t *stock, loop_state_t *state)
{
    state->buffer = serialize(state->buffer);
    if (state->cmd == -1 || my_strcmp(state->buffer, "exit") == 0)
        return true;
    state->last_exit = execute_command(stock, state->buffer);
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

static void set_shell_prompt(loop_state_t *state, main_t *stock)
{
    if (!state->prompt_displayed)
        write_print(stock);
    state->prompt_displayed = true;
    state->cmd = get_command(stock, &state->buffer, stock->history,
        get_user(stock->stock_env));
}

static void run_shell_loop(main_t *stock, loop_state_t *state)
{
    stock->last_exit = my_itoa(state->last_exit);
    while (my_strcmp(state->buffer, "exit") != 0) {
        handle_limit_signals(stock->signal->sfd, stock->signal);
        set_shell_prompt(state, stock);
        if (check_limit_signals(stock->signal))
            break;
        if (state->cmd == CONTINUE) {
            state->prompt_displayed = false;
            continue;
        }
        if (handle_command_result(stock, state))
            break;
        free_alloc(stock->last_exit);
        stock->last_exit = my_itoa(state->last_exit);
    }
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
