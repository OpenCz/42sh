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

static void print_command(char *buffer, int len)
{
    write(1, "\r\x1b[2K", 5);
    my_putstr("\033[90m╰─❯\033[0m ");
    write(1, buffer, len);
}

static int realloc_buffer(char **buffer, int len, int *repeat)
{
    if (len + 1 >= BUFFER_SIZE) {
        *buffer = realloc(*buffer, BUFFER_SIZE * *repeat);
        if (!(*buffer))
            return -1;
        *repeat += 1;
    }
    return 0;
}

static int append_char(char **buffer, char ch, int *len)
{
    (*buffer)[*len] = ch;
    *len += 1;
    (*buffer)[*len] = '\0';
    return 0;
}

static int specific_char(char ch, char **buffer, int *len)
{
    if (ch == 37 || ch == 38 || ch == 39 || ch == 40)
        return 1;
    if (ch == 127) {
        *len -= 1;
        return 1;
    }
    return 0;
}

static int check_char(char **buffer, int *repeat, int *len)
{
    char ch;

    if (read(STDIN_FILENO, &ch, 1) == -1)
        return -1;
    if (specific_char(ch, buffer, len) == 1)
        return 0;
    append_char(buffer, ch, len);
    if (ch == '\n')
        return write(1, "\n\x1b[2K", 5);
    if (realloc_buffer(buffer, *len, repeat) == -1)
        return -1;
    return 0;
}

static int create_command(char **buffer)
{
    int len = 0;
    int status = 0;
    struct termios tr;
    struct termios old;

    *buffer = malloc(BUFFER_SIZE + 1);
    if (!*buffer)
        return -1;
    init_termios(&tr, &old);
    for (int repeat = 2; status == 0;) {
        print_command(*buffer, len);
        status = check_char(buffer, &repeat, &len);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return status;
}

int get_command(char **buffer)
{
    size_t buffer_size = BUFFER_SIZE;

    if ((*buffer))
        free(*buffer);
    if (isatty(0)) {
        if (create_command(buffer) == -1) {
            return -1;
        }
    } else {
        if (getline(buffer, &buffer_size, stdin) == -1)
            return -1;
    }
    return 0;
}
