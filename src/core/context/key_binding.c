/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** key_binding
*/

#include "c_zsh.h"

int handle_ctrl_d(int *len, char *user, main_t *stock_main)
{
    if (*len == 0)
        return -1;
    my_putstr("\n");
    display_prompt(stock_main->czshrc->prompt, user);
    return 2;
}

int handle_ctrl_l(main_t *stock_main, char *user)
{
    execute_command(stock_main, "clear");
    display_prompt(stock_main->czshrc->prompt, user);
    return 2;
}

int handle_ctrl_c(buffer_t *buff, int *cursor, char *user,
    main_t *stock_main)
{
    my_putstr("\n");
    display_prompt(stock_main->czshrc->prompt, user);
    write(1, "\r\x1b[2K", 6);
    (*buff->buffer)[0] = '\0';
    *buff->len = 0;
    *cursor = 0;
    return 2;
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

int handle_input_char(history_t *history, buffer_t *buff,
    int *cursor, input_ctx_t *ctx)
{
    if (ctx->ch == 3)
        return handle_ctrl_c(buff, cursor, ctx->user, ctx->stock_main);
    if (ctx->ch == 12)
        return handle_ctrl_l(ctx->stock_main, ctx->user);
    if (ctx->ch == 4)
        return handle_ctrl_d(buff->len, ctx->user, ctx->stock_main);
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
