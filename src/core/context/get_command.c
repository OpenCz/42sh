/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Interactive input loop: create_command reads chars one by one
** in raw mode; check_char dispatches each byte to a key handler;
** get_command picks TTY path or falls back to getline().
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

static void print_command(char *buffer, int len, int cursor)
{
    int cursor_width = get_buffer_display_width(buffer, cursor);
    int total_width = get_buffer_display_width(buffer, len);

    write(1, "\r\x1b[2K", 5);
    my_putstr("\033[90m╰─❯\033[0m ");
    for (int i = 0; i < len && buffer[i]; i++) {
        if (buffer[i] == '\t')
            write_tab_spaces();
        else
            write(1, &buffer[i], 1);
    }
    for (int i = total_width; cursor_width < i; i--)
        write(1, "\b", 1);
}

int append_char(char **buffer, char ch, int *len, int *cursor)
{
    memmove(&(*buffer)[*cursor + 1], &(*buffer)[*cursor], *len - *cursor + 1);
    (*buffer)[*cursor] = ch;
    *len += 1;
    (*buffer)[*len] = '\0';
    *cursor += 1;
    return 0;
}

static int reset_prompt_status(int *cursor, int len)
{
    *cursor = len;
    return 0;
}

static int check_char(history_t *history, buffer_t *buff,
    int *cursor, input_ctx_t *ctx)
{
    if (read(STDIN_FILENO, &ctx->ch, 1) == -1)
        return -1;
    return handle_input_char(history, buff, cursor, ctx);
}

static int create_command(history_t *history, char **buffer,
    input_ctx_t *ctx)
{
    int len = 0;
    int status = 0;
    struct termios tr;
    struct termios old;

    (*buffer) = calloc(BUFFER_SIZE, 1);
    if (!*buffer)
        return -1;
    init_termios(&tr, &old);
    for (int cursor = 0; status == 0;) {
        print_command(*buffer, len, cursor);
        status = check_char(history,
            &(buffer_t){.buffer = buffer, .len = &len}, &cursor,
            ctx);
        if (status == 2)
            status = reset_prompt_status(&cursor, len);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return status;
}

static int manage_ignoreeof(main_t *stock_main)
{
    int countdown = 0;

    for (env_t *tmp = stock_main->stock_local_var; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, "ignoreeof") != 0)
            continue;
        countdown = atoi(tmp->value);
        if (countdown <= 0)
            return -1;
        countdown--;
        tmp->value = my_itoa(countdown);
        my_putstr("Use \"exit\" to leave the shell.\n");
        return 0;
    }
    return -1;
}

static int get_tty_command(main_t *stock_main, char **buffer,
    history_t *history, char *user)
{
    input_ctx_t ctx = {.user = user, .stock_main = stock_main};
    int create_cmd = create_command(history, buffer, &ctx);

    if (create_cmd == -1) {
        free_alloc(*buffer);
        *buffer = NULL;
        return manage_ignoreeof(stock_main);
    }
    if (create_cmd == CONTINUE)
        return CONTINUE;
    manage_history(history, buffer);
    return 0;
}

int get_command(main_t *stock_main, char **buffer, history_t *history,
    char *user)
{
    int status = 0;
    size_t buffer_size = BUFFER_SIZE;

    if (isatty(0)) {
        status = get_tty_command(stock_main, buffer, history, user);
        if (status != 0)
            return status;
    } else {
        if (getline(buffer, &buffer_size, stdin) == -1)
            return manage_ignoreeof(stock_main);
    }
    history->curr_cmd = NULL;
    return 0;
}
