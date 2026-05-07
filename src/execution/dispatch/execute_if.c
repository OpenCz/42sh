/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/execution/dispatch
** File description:
** execute_if.c
*/

#include "c_zsh.h"

static int count_keyword(const char *str, const char *kw)
{
    int count = 0;
    int klen = strlen(kw);
    int before = 0;
    int after = 0;
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

int is_if_segment(char *cmd)
{
    for (; *cmd == ' ' || *cmd == '\t'; cmd++);
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

    if (!merged)
        return NULL;
    strcpy(merged, cmds[start]);
    for (int i = start + 1; i <= end; i++) {
        strcat(merged, " ");
        strcat(merged, cmds[i]);
    }
    return merged;
}

static char *merge_if_block(char **cmds, int *idx)
{
    int start = *idx;
    int end = start;
    int depth = count_keyword(cmds[start], "if");
    size_t total_len = 0;

    depth -= count_keyword(cmds[start], "endif");
    total_len = scan_if_end(cmds, start, &end, depth);
    *idx = end;
    return build_merged_str(cmds, start, end, total_len);
}

int handle_if_segment(main_t *stock_main, char **cmds, int *i)
{
    char *merged = merge_if_block(cmds, i);
    int status = 0;

    if (!merged)
        return 1;
    status = execute_compound_command(stock_main, &merged);
    free_alloc(merged);
    return status;
}
