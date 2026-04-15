    /*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The color.h
*/
/**
 * @file color.h
 * @brief The color.h
 * @author Erwan Lo Presti
 */

#ifndef INC_42SH_COLOR_H
    #define INC_42SH_COLOR_H

#define ESC     "\033["
#define END     "m"
#define RESET   "\033[0m"

#define FG_BLACK    30
#define FG_RED      31
#define FG_GREEN    32
#define FG_YELLOW   33
#define FG_BLUE     34
#define FG_MAGENTA  35
#define FG_CYAN     36
#define FG_WHITE    37

#define FG_GRAY     90

#define BG_BLACK    40
#define BG_RED      41
#define BG_GREEN    42
#define BG_YELLOW   43
#define BG_BLUE     44
#define BG_MAGENTA  45
#define BG_CYAN     46
#define BG_WHITE    47

#define BG_GRAY     100

#define P_PINK         218
#define P_ROSE         224
#define P_PEACH        216
#define P_ORANGE       215
#define P_YELLOW       229

#define P_MINT         121
#define P_GREEN        157

#define P_SKY          117
#define P_BLUE         153

#define P_LAVENDER     183
#define P_PURPLE       177

#define P_SOFT_GRAY    245
#define P_LIGHT_GRAY   250

#define SH_NAME        FG_BLUE
#define SH_PATH        FG_CYAN
#define SH_SUCCESS     FG_GREEN
#define SH_ERROR       FG_RED
#define SH_SYMBOL      FG_YELLOW

#endif /* INC_42SH_COLOR_H */
