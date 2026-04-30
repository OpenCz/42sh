/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** ANSI escape-code macros for terminal color output.
** Defines foreground/background constants (BLACK, RED, GREEN,
** YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET) for prompt output.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#ifndef INC_42SH_COLOR_H
    #define INC_42SH_COLOR_H

    #define ESC "\033["
    #define END "m"
    #define RESET "\033[0m"

    #define DEFAULT 0

    #define FG_BLACK 30
    #define FG_RED 31
    #define FG_GREEN 32
    #define FG_YELLOW 33
    #define FG_BLUE 34
    #define FG_MAGENTA 35
    #define FG_CYAN 36
    #define FG_WHITE 37
    #define FG_GRAY 90
    #define FG_BRIGHT_RED 91
    #define FG_BRIGHT_GREEN 92
    #define FG_BRIGHT_YELLOW 93
    #define FG_BRIGHT_BLUE 94
    #define FG_BRIGHT_MAGENTA 95
    #define FG_BRIGHT_CYAN 96
    #define FG_BRIGHT_WHITE 97

    #define BG_BLACK 40
    #define BG_RED 41
    #define BG_GREEN 42
    #define BG_YELLOW 43
    #define BG_BLUE 44
    #define BG_MAGENTA 45
    #define BG_CYAN 46
    #define BG_WHITE 47
    #define BG_GRAY 100
    #define BG_BRIGHT_RED 101
    #define BG_BRIGHT_GREEN 102
    #define BG_BRIGHT_YELLOW 103
    #define BG_BRIGHT_BLUE 104
    #define BG_BRIGHT_MAGENTA 105
    #define BG_BRIGHT_CYAN 106
    #define BG_BRIGHT_WHITE 107

    #define P_PINK 218
    #define P_ROSE 224
    #define P_PEACH 216
    #define P_ORANGE 215
    #define P_YELLOW 229

    #define P_MINT 121
    #define P_GREEN 157
    #define P_SKY 117
    #define P_BLUE 153
    #define P_LAVENDER 183
    #define P_PURPLE 177
    #define P_SOFT_GRAY 245
    #define P_LIGHT_GRAY 250

    #define COLOR_256_BASE 256
    #define FG_PINK (COLOR_256_BASE + P_PINK)
    #define FG_ROSE (COLOR_256_BASE + P_ROSE)
    #define FG_PEACH (COLOR_256_BASE + P_PEACH)
    #define FG_ORANGE (COLOR_256_BASE + P_ORANGE)
    #define FG_PALE_YELLOW (COLOR_256_BASE + P_YELLOW)
    #define FG_MINT (COLOR_256_BASE + P_MINT)
    #define FG_SPRING_GREEN (COLOR_256_BASE + P_GREEN)
    #define FG_SKY (COLOR_256_BASE + P_SKY)
    #define FG_LIGHT_BLUE (COLOR_256_BASE + P_BLUE)
    #define FG_LAVENDER (COLOR_256_BASE + P_LAVENDER)
    #define FG_PURPLE (COLOR_256_BASE + P_PURPLE)
    #define FG_SOFT_GRAY (COLOR_256_BASE + P_SOFT_GRAY)
    #define FG_LIGHT_GRAY (COLOR_256_BASE + P_LIGHT_GRAY)

    #define BG_PINK (COLOR_256_BASE + P_PINK)
    #define BG_ROSE (COLOR_256_BASE + P_ROSE)
    #define BG_PEACH (COLOR_256_BASE + P_PEACH)
    #define BG_ORANGE (COLOR_256_BASE + P_ORANGE)
    #define BG_PALE_YELLOW (COLOR_256_BASE + P_YELLOW)
    #define BG_MINT (COLOR_256_BASE + P_MINT)
    #define BG_SPRING_GREEN (COLOR_256_BASE + P_GREEN)
    #define BG_SKY (COLOR_256_BASE + P_SKY)
    #define BG_LIGHT_BLUE (COLOR_256_BASE + P_BLUE)
    #define BG_LAVENDER (COLOR_256_BASE + P_LAVENDER)
    #define BG_PURPLE (COLOR_256_BASE + P_PURPLE)
    #define BG_SOFT_GRAY (COLOR_256_BASE + P_SOFT_GRAY)
    #define BG_LIGHT_GRAY (COLOR_256_BASE + P_LIGHT_GRAY)

    #define SH_NAME FG_BLUE
    #define SH_PATH FG_CYAN
    #define SH_SUCCESS FG_GREEN
    #define SH_ERROR FG_RED
    #define SH_SYMBOL FG_YELLOW

#endif
