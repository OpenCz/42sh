/*
** EPITECH PROJECT, 2026
** instaler
** File description:
** core
*/

#ifndef CORE_H
    #define CORE_H
    #include "../instaler.h"
    #define NB_PROMPT 5
    #define NB_CYCLE_COLORS 15
    #define MAX_ALIASES 32
    #define ALIAS_NAME_MAX 32
    #define ALIAS_CMD_MAX 128
    #define ALIAS_VIEWPORT 5
typedef struct vector_s {
    int x;
    int y;
} vector_t;

typedef enum state_e {
    END,
    STEP_1,
    STEP_2,
    QUICK,
    DONE,
    ALIAS_EDIT,
} state_t;

typedef enum date_fmt_e {
    FMT_LONG,
    FMT_EU,
    FMT_US,
    FMT_ISO,
    NB_DATE_FMTS,
} date_fmt_t;

typedef struct button_s {
    state_t state;
    vector_t pos;
    char *text;
    struct button_s *next;
} button_t;

typedef struct prompt_item_s {
    char *key;
    bool enabled;
    int fg;
    int bg;
} prompt_item_t;

typedef struct alias_s {
    char name[ALIAS_NAME_MAX];
    char cmd[ALIAS_CMD_MAX];
    bool enabled;
} alias_t;

typedef struct alias_edit_s {
    int idx;
    int field;
    char name[ALIAS_NAME_MAX];
    char cmd[ALIAS_CMD_MAX];
    int name_pos;
    int cmd_pos;
} alias_edit_t;

typedef struct preferences_s {
    prompt_item_t prompt[NB_PROMPT];
    date_fmt_t date_fmt;
    alias_t aliases[MAX_ALIASES];
    int nb_aliases;
    int alias_scroll;
    int row;
    int col;
} preferences_t;

typedef struct instaler_s {
    vector_t size;
    WINDOW *window;
    state_t state;
    button_t *buttons;
    preferences_t prefs;
    alias_edit_t alias_edit;
} instaler_t;
void loop(instaler_t *instaler);
#endif
