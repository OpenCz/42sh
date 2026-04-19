/*
** EPITECH PROJECT, 2026
** execute
** File description:
** command
*/

#include <termios.h>
#include "c_zsh.h"

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

static int handle_ctrl_l(char ch)
{
    pid_t pid;
    char *av[] = {"clear", NULL};

    pid = fork();
    if (pid == 0) {
        execv("/bin/clear", av);
    } else
        waitpid(pid, NULL, 0);
    display_prompt();
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

static int handle_ctrl_d(int *len, char *user)
{
    if (*len == 0)
        return -1;
    write(1, "\n", 1);
    display_prompt(user);
    return 2;
}

static int handle_ctrl_c(char ch)
{
    if (ch == 3) {
        write(1, "\n", 1);
        return -1;
    }
    return 0;
}

static int check_char(history_t *history, buffer_t *buff,
    int *cursor, char *user)
{
    char ch = 0;

    if (read(STDIN_FILENO, &ch, 1) == -1 || handle_ctrl_c(ch) == -1)
        return -1;
    if (ch == 3)
        return 0;
    if (ch == 12)
        return handle_ctrl_l(ch);
    if (ch == 4)
        return handle_ctrl_d(buff->len, user);
    if (ch == ARROW_START)
        return arrow_handling(history, buff->buffer, cursor, buff->len);
    if (specific_char(ch, buff->buffer, buff->len, cursor) == 1)
        return 0;
    if (ch == '\n') {
        write(1, "\n", 1);
        return 1;
    }
    append_char(buff->buffer, ch, buff->len, cursor);
    return 0;
}

static int create_command(history_t *history, char **buffer, char *user)
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
            &(buffer_t){.buffer = buffer, .len = &len}, &cursor, user);
        if (status == 2) {
            status = 0;
            cursor = len;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return status;
}

int get_command(char **buffer, history_t *history, char *user)
{
    size_t buffer_size = BUFFER_SIZE;
    int create_cmd = 0;

    if (isatty(0)) {
        create_cmd = create_command(history, buffer, user);
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
