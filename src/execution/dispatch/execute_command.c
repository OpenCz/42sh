/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Top-level dispatcher: splits input on ';' respecting quotes,
** then routes each segment to execute_pipeline (pipe present),
** execute_operator (&& or ||), or execute_single_command.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static void update_quote_state(char c, int *in_single, int *in_double,
    int *in_backtick)
{
    if (c == '\'' && !(*in_double) && !(*in_backtick))
        *in_single = !(*in_single);
    if (c == '"' && !(*in_single) && !(*in_backtick))
        *in_double = !(*in_double);
    if (c == '`' && !(*in_single) && !(*in_double))
        *in_backtick = !(*in_backtick);
}

static int is_pipe_operator(char c, int i, char *cmd)
{
    if (c != '|')
        return 0;
    if (i > 0 && cmd[i - 1] == '|')
        return 0;
    if (cmd[i + 1] != '\0' && cmd[i + 1] == '|')
        return 0;
    return 1;
}

int has_pipeline_operator(char *command)
{
    int in_single = 0;
    int in_double = 0;
    int in_backtick = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        update_quote_state(command[i], &in_single, &in_double, &in_backtick);
        if (in_single || in_double || in_backtick)
            continue;
        if (is_pipe_operator(command[i], i, command))
            return 1;
    }
    return 0;
}

static int execute_logic_or_pipe(main_t *stock_main, char *command,
    int has_logic, int has_pipe)
{
    if (has_logic)
        return execute_operator(stock_main, command);
    if (has_pipe)
        return execute_pipeline(stock_main, command);
    return -1;
}

static void apply_job_control(char *command, int cmd_l, char *buf)
{
    strncpy(buf, command, cmd_l - 2);
    buf[cmd_l - 2] = '\0';
}

static int execute_compound_command(main_t *stock_main, char **command_ptr)
{
    char *command = NULL;
    int is_job = 0;
    char buf[LINE_SIZE] = {0};

    expand_aliases(stock_main, command_ptr);
    command = *command_ptr;
    if (my_strstr(command, "&&") || my_strstr(command, "||") ||
        has_pipeline_operator(command))
        return execute_logic_or_pipe(stock_main, command,
            !!(my_strstr(command, "&&") || my_strstr(command, "||")),
            has_pipeline_operator(command));
    is_job = (strlen(command) > 1 && command[strlen(command) - 1] == '&' &&
        command[strlen(command) - 2] == ' ');
    if (is_job) {
        apply_job_control(command, strlen(command), buf);
        command = buf;
    }
    return execute_single_command(stock_main, command, true, is_job);
}

int execute_command(main_t *stock_main, char *command)
{
    char **commands = my_str_to_word_array_quote(command, ";");
    int last_status = 0;

    if (!commands)
        return 1;
    for (int i = 0; commands[i] != NULL; i++)
        last_status = execute_compound_command(stock_main, &commands[i]);
    free_array(commands);
    return last_status;
}
