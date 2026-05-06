/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** menu.c
*/

#include "c_zsh.h"

static int get_available_lines(void)
{
    struct winsize w;
    int rows = 0;
    int cols = 0;
    int cur_row = 0;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return AUTOCOMPLETION;
    rows = w.ws_row;
    printf("\x1b[6n");
    fflush(stdout);
    if (scanf("\x1b[%d;%dR", &cur_row, &cols) != 2)
        return AUTOCOMPLETION;
    if (rows - cur_row < 3)
        return 3;
    return (rows - cur_row);
}

void render_list(char **names, int idx, int shown)
{
    int count = len_array(names);
    int start = idx - shown / 2;

    if (start < 0)
        start = 0;
    if (start + shown > count)
        start = count - shown;
    for (int i = start; i < start + shown; i++) {
        printf("\x1b[2K");
        if (i == idx)
            printf(" \x1b[1;30;47m %s \x1b[0m\n", names[i]);
        else
            printf("  %s\n", names[i]);
    }
    fflush(stdout);
}

static void clear_list(int shown)
{
    if (shown <= 0)
        return;
    printf("\x1b[%dA", shown + 2);
    for (int i = 0; i < shown + 2; i++)
        printf("\x1b[2K\n");
    printf("\x1b[%dA", shown + 2);
    fflush(stdout);
}

static void enter_completion(char **names, int idx, buffer_t *buf)
{
    char *name = NULL;

    for (int i = 0; names[i] != NULL; i++)
        if (idx == i)
            name = names[i];
    if (!name)
        return;
    while (*buf->cursor > 0 && (*buf->buffer)[*buf->cursor - 1] != ' ') {
        (*buf->cursor)--;
        (*buf->len)--;
    }
    for (int i = 0; name[i] != '\0'; i++) {
        (*buf->buffer)[*buf->cursor] = name[i];
        (*buf->cursor)++;
        (*buf->len)++;
    }
    (*buf->buffer)[*buf->cursor] = '\0';
}

static bool process_menu_input(char **names, int *idx, int shown, buffer_t *buf)
{
    char arrow[3] = {0};

    if (read(STDIN_FILENO, &arrow[0], 1) != 1)
        return true;
    if (arrow[0] == '\n') {
        enter_completion(names, *idx, buf);
        return false;
    }
    if (arrow[0] == '\t') {
        handle_menu_arrow(names, idx, "\e[T", shown);
        return true;
    }
    if (arrow[0] != '\e' || check_escape(arrow))
        return false;
    handle_menu_arrow(names, idx, arrow, shown);
    return true;
}

static void menu_loop(char **names, int count, int shown, buffer_t *buf)
{
    int idx = 0;

    printf("\n");
    render_list(names, idx, shown);
    while (process_menu_input(names, &idx, shown, buf));
    clear_list(shown);
}

static void setup_menu_termios(struct termios *old)
{
    struct termios tr;

    tcgetattr(STDIN_FILENO, old);
    tr = *old;
    tr.c_lflag &= ~(ICANON | ECHO);
    tr.c_cc[VMIN] = 0;
    tr.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &tr);
    printf("\x1b[?25l");
    fflush(stdout);
}

int menu(char **names, main_t *stock_main, buffer_t *buf)
{
    struct termios old;
    int count = len_array(names);
    int shown = get_available_lines();

    if (shown > count)
        shown = count;
    setup_menu_termios(&old);
    menu_loop(names, count, shown, buf);
    printf("\x1b[?25h");
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    display_prompt(stock_main->czshrc->prompt,
        get_user(stock_main->stock_env));
    return 0;
}
