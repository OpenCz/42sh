/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "c_zsh.h"

static char *serialize(char *buffer)
{
    size_t len = 0;

    if (!buffer)
        return NULL;
    len = my_strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    return buffer;
}

static bool handle_command_result(main_t *stock, loop_state_t *state)
{
    state->buffer = serialize(state->buffer);
    if (state->cmd == -1 || my_strcmp(state->buffer, "exit") == 0)
        return true;
    state->last_exit = execute_command(stock, state->buffer);
    if (state->last_exit == 130) {
        display_prompt(get_user(stock->stock_env));
        state->prompt_displayed = true;
    } else {
        state->prompt_displayed = false;
    }
    return false;
}

static void run_shell_loop(main_t *stock, loop_state_t *state)
{
    stock->last_exit = my_itoa(state->last_exit);
    while (my_strcmp(state->buffer, "exit") != 0) {
        if (!state->prompt_displayed)
            write_print(stock);
        state->prompt_displayed = true;
        state->cmd = get_command(stock, &state->buffer, stock->history,
            get_user(stock->stock_env));
        if (state->cmd == CONTINUE) {
            state->prompt_displayed = false;
            continue;
        }
        if (handle_command_result(stock, state))
            break;
        stock->last_exit = my_itoa(state->last_exit);
    }
    write_tty("exit\n", state->cmd);
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

    setup_shell_signals();
    run_shell_loop(stock, &state);
    write_tty("exit\n", state.cmd);
    free_main(stock);
    return state.last_exit;
}
