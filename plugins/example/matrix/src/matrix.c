/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/plugins
** File description:
** Matrix example plugin
*/

#include "c_zsh.h"
#include "matrix.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

static char random_glyph(void)
{
    const char glyphs[] = "01ABCDEFGHIJKLMNOPQRSTUVWXYZ@#$%&*+-";

    return glyphs[rand() % (sizeof(glyphs) - 1)];
}

static void print_cell(int drop, int row)
{
    if (drop == row)
        printf("\033[1;92m%c\033[0m", random_glyph());
    else if (drop > row && drop - row < 4)
        printf("\033[0;32m%c\033[0m", random_glyph());
    else
        putchar(' ');
}

static void display_matrix_frame(int *drops, int rows, int cols)
{
    printf("\033[H\033[2J");
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            print_cell(drops[col], row);
        putchar('\n');
    }
    fflush(stdout);
}

static void update_drops(int *drops, int cols, int rows)
{
    for (int col = 0; col < cols; col++) {
        if (drops[col] > rows + (rand() % 12))
            drops[col] = rand() % rows;
        else
            drops[col]++;
    }
}

static void run_matrix(int *drops, int rows, int cols, int time_v)
{
    for (int frame = 0; frame < time_v * 12; frame++) {
        display_matrix_frame(drops, rows, cols);
        update_drops(drops, cols, rows);
        usleep(80000);
    }
}

void matrix(int time_v)
{
    struct termios old;
    int rows = 24;
    int cols = 80;
    int *drops = NULL;
    time_t timer = time(NULL);

    if (time_v <= 0)
        time_v = 10;
    get_terminal_size(&rows, &cols);
    drops = calloc((size_t)cols, sizeof(int));
    if (!drops)
        return;
    tcgetattr(STDIN_FILENO, &old);
    set_blank_term();
    srand((u_int16_t)(timer));
    printf("\033[?25l\033[2J\033[H");
    fflush(stdout);
    run_matrix(drops, rows, cols, time_v);
    restore_terminal(&old);
    free(drops);
}

static int matrix_builtin(main_t *main_stock, command_ctx_t *ctx)
{
    int time = -1;

    (void)main_stock;
    if (ctx->arg_command[0])
        time = atoi(ctx->arg_command[0]);
    matrix(time);
    return 0;
}

int czsh_plugin_init(main_t *main_stock, const shell_plugin_api_t *api)
{
    if (!api || api->abi_version != CZSH_PLUGIN_ABI_VERSION)
        return CZSH_PLUGIN_ERR;
    if (!api->register_builtin)
        return CZSH_PLUGIN_ERR;
    return api->register_builtin(main_stock, "matrix", matrix_builtin,
        api->plugin_handle);
}

void czsh_plugin_shutdown(main_t *main_stock)
{
    (void)main_stock;
}
