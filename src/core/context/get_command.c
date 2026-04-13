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
    tr->c_lflag &= ~(ICANON | ECHO);
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
    int i = *len;

    for (; i > *cursor; i--)
        (*buffer)[i + 1] = (*buffer)[i];
    (*buffer)[i] = ch;
    *len += 1;
    (*buffer)[*len] = '\0';
    *cursor += 1;
    return 0;
}

static int specific_char(char ch, char **buffer, int *len, int *cursor)
{
    if (arrow_handling(ch, cursor, *len) == 1)
        return 1;
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

static int check_char(char **buffer, int *repeat,
    int *len, int *cursor)
{
    char ch;

    if (read(STDIN_FILENO, &ch, 1) == -1)
        return -1;
    if (specific_char(ch, buffer, len, cursor) == 1)
        return 0;
    append_char(buffer, ch, len, cursor);
    if (ch == '\n')
        return write(1, "\n\x1b[2K", 5);
    return 0;
}

static int create_command(char **buffer)
{
    int len = 0;
    int status = 0;
    struct termios tr;
    struct termios old;
    int cursor = 0;

    (*buffer) = malloc(BUFFER_SIZE);
    if (!*buffer)
        return -1;
    init_termios(&tr, &old);
    for (int repeat = 2; status == 0;) {
        print_command(*buffer, len, cursor);
        status = check_char(buffer, &repeat, &len, &cursor);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return status;
}

int get_command(char **buffer, history_t *history)
{
    size_t buffer_size = BUFFER_SIZE;

    if ((*buffer))
        free(*buffer);
    if (isatty(0)) {
        if (create_command(buffer) == -1)
            return -1;
        manage_history(history, *buffer);
    } else {
        if (getline(buffer, &buffer_size, stdin) == -1)
            return -1;
    }
    return 0;
}
