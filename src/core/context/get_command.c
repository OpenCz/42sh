/*
** EPITECH PROJECT, 2026
** execute
** File description:
** command
*/
#include <termios.h>
#include "../../../include/minishell.h"

static void init_termios(struct termios *tr, struct termios *old)
{
    tcgetattr(STDIN_FILENO, old);
    tcgetattr(STDIN_FILENO, tr);
    tr->c_lflag &= ~(ICANON | ECHO | ISIG);
    tr->c_cc[VMIN] = 1;
    tr->c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, tr);
}

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

static int handle_ctrl_d(int *len)
{
    if (*len == 0)
        return -1;
    write(1, "\n", 1);
    display_prompt();
    return 2;
}

static int check_char(history_t *history, char **buffer, int *len, int *cursor)
{
    char ch = 0;

    if (read(STDIN_FILENO, &ch, 1) == -1)
        return -1;
    if (ch == 3)
        return 0;
    if (ch == 4)
        return handle_ctrl_d(len);
    if (ch == ARROW_START)
        return arrow_handling(history, buffer, cursor, len);
    if (specific_char(ch, buffer, len, cursor) == 1)
        return 0;
    if (ch == '\n') {
        write(1, "\n", 1);
        return 1;
    }
    append_char(buffer, ch, len, cursor);
    return 0;
}

static int create_command(history_t *history, char **buffer)
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
        status = check_char(history, buffer, &len, &cursor);
        if (status == 2) {
            status = 0;
            cursor = len;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return status;
}

int get_command(char **buffer, history_t *history)
{
    size_t buffer_size = BUFFER_SIZE;
    int create_cmd = 0;

    if (isatty(0)) {
        create_cmd = create_command(history, buffer);
        if (create_cmd == -1)
            return -1;
        if (create_cmd == CONTINUE)
            return CONTINUE;
        manage_history(history, *buffer);
    } else {
        if (getline(buffer, &buffer_size, stdin) == -1)
            return -1;
    }
    history->curr_cmd = NULL;
    return 0;
}
