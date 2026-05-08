/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** preferences
*/

#include "installer/install.h"

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

static void add_alias(preferences_t *prefs, char *name, char *cmd)
{
    int alias_idx = prefs->nb_aliases;

    if (alias_idx >= MAX_ALIASES)
        return;
    strncpy(prefs->aliases[alias_idx].name, name, ALIAS_NAME_MAX - 1);
    prefs->aliases[alias_idx].name[ALIAS_NAME_MAX - 1] = '\0';
    strncpy(prefs->aliases[alias_idx].cmd, cmd, ALIAS_CMD_MAX - 1);
    prefs->aliases[alias_idx].cmd[ALIAS_CMD_MAX - 1] = '\0';
    prefs->aliases[alias_idx].enabled = true;
    prefs->nb_aliases++;
}

static void add_aliases(preferences_t *prefs)
{
    add_alias(prefs, "..", "cd ..");
    add_alias(prefs, "...", "cd ../..");
    add_alias(prefs, "home", "cd ~");
    add_alias(prefs, "ll", "ls -la --color=auto");
    add_alias(prefs, "la", "ls -A --color=auto");
    add_alias(prefs, "lt", "ls -lt --color=auto");
    add_alias(prefs, "gs", "git status");
    add_alias(prefs, "gp", "git push");
    add_alias(prefs, "gl", "git log --oneline");
}

void init_preferences(instaler_t *instaler)
{
    preferences_t *prefs = &instaler->prefs;
    char *prompt_keys[NB_PROMPT] = {"user", "folder", "git_branch", "date",
        "time"};
    int fg_colors[NB_PROMPT] = {0, 0, 0, 0, 0};
    int bg_colors[NB_PROMPT] = {7, 4, 1, 7, 2};

    prefs->row = 0;
    prefs->col = 0;
    prefs->alias_scroll = 0;
    prefs->nb_aliases = 0;
    prefs->date_fmt = FMT_LONG;
    for (int i = 0; i < NB_PROMPT; i++) {
        prefs->prompt[i].key = prompt_keys[i];
        prefs->prompt[i].enabled = true;
        prefs->prompt[i].fg = fg_colors[i];
        prefs->prompt[i].bg = bg_colors[i];
    }
    add_aliases(prefs);
}
