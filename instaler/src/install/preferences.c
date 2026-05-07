/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** preferences
*/

#include "../../include/instaler.h"

char *get_cycle_color(int i)
{
    char *colors[NB_CYCLE_COLORS] = {
        "BLACK", "RED", "GREEN", "YELLOW", "BLUE",
        "MAGENTA", "CYAN", "WHITE", "GRAY",
        "PINK", "ORANGE", "MINT", "SKY", "LAVENDER", "NONE"
    };

    return colors[i];
}

char *get_date_fmt_str(date_fmt_t fmt)
{
    if (fmt == FMT_EU)
        return "EU";
    if (fmt == FMT_US)
        return "US";
    if (fmt == FMT_ISO)
        return "ISO";
    return "LONG";
}

static void add_alias(preferences_t *p, char *name, char *cmd)
{
    int i = p->nb_aliases;

    if (i >= MAX_ALIASES)
        return;
    strncpy(p->aliases[i].name, name, ALIAS_NAME_MAX - 1);
    p->aliases[i].name[ALIAS_NAME_MAX - 1] = '\0';
    strncpy(p->aliases[i].cmd, cmd, ALIAS_CMD_MAX - 1);
    p->aliases[i].cmd[ALIAS_CMD_MAX - 1] = '\0';
    p->aliases[i].enabled = true;
    p->nb_aliases++;
}

void add_aliases(preferences_t *p)
{
    add_alias(p, "..", "cd ..");
    add_alias(p, "...", "cd ../..");
    add_alias(p, "home", "cd ~");
    add_alias(p, "ll", "ls -la --color=auto");
    add_alias(p, "la", "ls -A --color=auto");
    add_alias(p, "lt", "ls -lt --color=auto");
    add_alias(p, "gs", "git status");
    add_alias(p, "gp", "git push");
    add_alias(p, "gl", "git log --oneline");
}

void init_preferences(instaler_t *instaler)
{
    preferences_t *p = &instaler->prefs;
    char *keys[NB_PROMPT] = {"user", "folder", "git_branch", "date", "time"};
    int fgs[NB_PROMPT] = {0, 0, 0, 0, 0};
    int bgs[NB_PROMPT] = {7, 4, 1, 7, 2};

    p->row = 0;
    p->col = 0;
    p->alias_scroll = 0;
    p->nb_aliases = 0;
    p->date_fmt = FMT_LONG;
    for (int i = 0; i < NB_PROMPT; i++) {
        p->prompt[i].key = keys[i];
        p->prompt[i].enabled = true;
        p->prompt[i].fg = fgs[i];
        p->prompt[i].bg = bgs[i];
    }
    add_aliases(p);
}
