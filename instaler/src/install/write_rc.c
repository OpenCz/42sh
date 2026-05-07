/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** write_rc
*/

#include "../../include/instaler.h"
#include <sys/stat.h>

static char *get_prompt_comment(int i)
{
    char *comments[NB_PROMPT] = {
        "Affiche le nom de l'utilisateur (ex: sacha)",
        "Affiche le dossier courant (ex: ~/projects/42sh)",
        "Affiche la branche git si dans un repo (ex: main)",
        "Affiche la date",
        "Affiche l'heure (ex: 14:32:07)",
    };

    return comments[i];
}

static void write_prompt_item(FILE *f, prompt_item_t *item, char *comment)
{
    fprintf(f, "# %s\n", comment);
    fprintf(f, "%-12s= %-6s: %-14s: %s\n",
        item->key,
        item->enabled ? "true" : "false",
        get_cycle_color(item->fg),
        get_cycle_color(item->bg));
    fprintf(f, "\n");
}

static void write_date_item(FILE *f, preferences_t *prefs)
{
    prompt_item_t *item = &prefs->prompt[3];

    fprintf(f, "# Affiche la date — formats : LONG / EU / US / ISO\n");
    fprintf(f, "%-12s= %-6s: %-14s: %s\n",
        item->key,
        item->enabled ? "true" : "false",
        get_cycle_color(item->fg),
        get_cycle_color(item->bg));
    fprintf(f, "date_format = %s\n\n", get_date_fmt_str(prefs->date_fmt));
}

static void write_static_header(FILE *out)
{
    char *header = openator("assets/czshrc_header");

    if (!header)
        return;
    fputs(header, out);
    free(header);
}

static void write_prompt_section(FILE *f, preferences_t *prefs)
{
    for (int i = 0; i < NB_PROMPT; i++) {
        if (i == 3) {
            write_date_item(f, prefs);
            continue;
        }
        write_prompt_item(f, &prefs->prompt[i], get_prompt_comment(i));
    }
    fprintf(f, "# ============================================\n\n");
}

static void write_alias_section(FILE *f, preferences_t *prefs)
{
    fprintf(f, "[alias]\n\n");
    for (int i = 0; i < prefs->nb_aliases; i++) {
        if (prefs->aliases[i].enabled)
            fprintf(f, "%-8s= %s\n",
                prefs->aliases[i].name, prefs->aliases[i].cmd);
    }
}

static char *get_rc_path(const char *home, char *path, size_t size)
{
    char *os = detect_os();

    if (strcmp(os, "nixos") == 0) {
        snprintf(path, size, "%s/.config/42sh", home);
        mkdir(path, 0755);
        snprintf(path, size, "%s/.config/42sh/.czshrc", home);
    } else {
        snprintf(path, size, "%s/.czshrc", home);
    }
    free(os);
    return path;
}

void write_rc(preferences_t *prefs)
{
    char *home = getenv("HOME");
    char path[512];
    FILE *f;

    if (!home)
        return;
    get_rc_path(home, path, sizeof(path));
    f = fopen(path, "w");
    if (!f)
        return;
    write_static_header(f);
    write_prompt_section(f, prefs);
    write_alias_section(f, prefs);
    fclose(f);
}
