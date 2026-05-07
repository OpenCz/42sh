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

int has_pipeline_operator(char *command)
{
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] != '|')
            continue;
        if ((i == 0 || command[i - 1] != '|') &&
            (command[i + 1] == '\0' || command[i + 1] != '|'))
            return 1;
    }
    return 0;
}

static int execute_compound_command(main_t *stock_main, char *command)
{
    int has_logic_operator = (my_strstr(command, "&&") != NULL ||
        my_strstr(command, "||") != NULL);
    int has_pipe_operator = has_pipeline_operator(command);
    int cmd_len = strlen(command);
    int is_job_controler = (cmd_len > 1 && command[cmd_len - 1] == '&'
        && command[cmd_len - 2] == ' ');
    char buf[BUFFER_SIZE] = {0};

    expand_aliases(stock_main, &command);
    if (has_logic_operator)
        return execute_operator(stock_main, command);
    if (has_pipe_operator)
        return execute_pipeline(stock_main, command);
    if (is_job_controler) {
        strncpy(buf, command, cmd_len - 2);
        buf[cmd_len - 2] = '\0';
        command = buf;
    }
    return execute_single_command(stock_main, command, true, is_job_controler);
}

static int count_keyword(const char *str, const char *kw)
{
    int count = 0;
    int klen = strlen(kw);
    int before;
    int after;
    const char *p = str;

    p = strstr(p, kw);
    while (p != NULL) {
        before = (p == str || p[-1] == ' ' || p[-1] == '\t');
        after = (p[klen] == '\0' || p[klen] == ' ' || p[klen] == '\t');
        if (before && after)
            count++;
        p += klen;
        p = strstr(p, kw);
    }
    return count;
}

static int is_if_segment(char *cmd)
{
    while (*cmd == ' ' || *cmd == '\t')
        cmd++;
    return (strncmp(cmd, "if ", 3) == 0 || strcmp(cmd, "if") == 0);
}

static size_t scan_if_end(char **cmds, int start, int *end, int depth)
{
    size_t total_len = strlen(cmds[start]);

    while (depth > 0 && cmds[*end + 1]) {
        *end += 1;
        depth += count_keyword(cmds[*end], "if");
        depth -= count_keyword(cmds[*end], "endif");
        total_len += strlen(cmds[*end]) + 1;
    }
    return total_len;
}

static char *build_merged_str(char **cmds, int start, int end, size_t len)
{
    char *merged = calloc(len + 1, 1);
    int i;

    if (!merged)
        return NULL;
    strcpy(merged, cmds[start]);
    for (i = start + 1; i <= end; i++) {
        strcat(merged, " ");
        strcat(merged, cmds[i]);
    }
    return merged;
}

static char *merge_if_block(char **cmds, int *idx)
{
    int start = *idx;
    int end = start;
    int depth;
    size_t total_len;

    depth = count_keyword(cmds[start], "if");
    depth -= count_keyword(cmds[start], "endif");
    total_len = scan_if_end(cmds, start, &end, depth);
    *idx = end;
    return build_merged_str(cmds, start, end, total_len);
}

static int handle_if_segment(main_t *stock_main, char **cmds, int *i)
{
    char *merged;
    int status;

    merged = merge_if_block(cmds, i);
    if (!merged)
        return 1;
    status = execute_compound_command(stock_main, merged);
    free(merged);
    return status;
}

int execute_command(main_t *stock_main, char *command)
{
    char **commands;
    int last_status = 0;
    int i;

    commands = my_str_to_word_array_quote(command, ";");
    if (!commands)
        return 1;
    for (i = 0; commands[i] != NULL; i++) {
        if (is_if_segment(commands[i]))
            last_status = handle_if_segment(stock_main, commands, &i);
        else
            last_status = execute_compound_command(stock_main, commands[i]);
    }
    free_array(commands);
    return last_status;
}
