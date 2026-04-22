/*
** EPITECH PROJECT, 2026
** execute
** File description:
** command
*/

#include "c_zsh.h"

static void print_command(char *buffer, int len, int cursor)
{
    write(1, "\r\x1b[2K", 5);
    my_putstr("\033[90m╰─❯\033[0m ");
    write(1, buffer, cursor);
    write(1, &buffer[cursor], len - cursor);
    for (int i = len; cursor < i; i--)
        write(1, "\b", 1);
}

static int append_char(char **buffer, char ch, int *len, int *cursor)
{
    memmove(&(*buffer)[*cursor + 1], &(*buffer)[*cursor], *len - *cursor + 1);
    (*buffer)[*cursor] = ch;
    *len += 1;
    (*buffer)[*len] = '\0';
    *cursor += 1;
    return 0;
}

static int specific_char(char ch, char **buffer, int *len, int *cursor)
{
    if (ch == 1) {
        *cursor = 0;
        return 1;
    }
    if (ch == 5) {
        *cursor = *len;
        return 1;
    }
    if (ch == 127) {
        if (*cursor == 0)
            return 1;
        memmove(&(*buffer)[*cursor - 1],
            &(*buffer)[*cursor], *len - *cursor + 1);
        *len -= (*len > 0 ? 1 : 0);
        *cursor -= (*cursor > 0 ? 1 : 0);
        return 1;
    }
    return 0;
}

static int handle_regular_char(buffer_t *buff, int *cursor, char ch)
{
    append_char(buff->buffer, ch, buff->len, cursor);
    return 0;
}

static int reset_prompt_status(int *cursor, int len)
{
    *cursor = len;
    return 0;
}

static int handle_input_char(history_t *history, buffer_t *buff,
    int *cursor, input_ctx_t *ctx)
{
    if (ctx->ch == 3) {
        my_putstr("\n");
        display_prompt(ctx->user);
        return 0;
    }
    if (ctx->ch == 12)
        return handle_ctrl_l(ctx->stock_main, ctx->user);
    if (ctx->ch == 4)
        return handle_ctrl_d(buff->len, ctx->user);
    if (ctx->ch == ARROW_START)
        return arrow_handling(history, buff->buffer, cursor, buff->len);
    if (specific_char(ctx->ch, buff->buffer, buff->len, cursor) == 1)
        return 0;
    if (ctx->ch == '\n') {
        my_putstr("\n");
        return 1;
    }
    return handle_regular_char(buff, cursor, ctx->ch);
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

static int get_tty_command(main_t *stock_main, char **buffer,
    history_t *history, char *user)
{
    input_ctx_t ctx = {.user = user, .stock_main = stock_main};
    int create_cmd = create_command(history, buffer, &ctx);

    if (create_cmd == -1) {
        free_alloc(*buffer);
        *buffer = NULL;
        return -1;
    }
    if (create_cmd == CONTINUE)
        return CONTINUE;
    manage_history(history, *buffer);
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
            return -1;
    }
    history->curr_cmd = NULL;
    return 0;
}
