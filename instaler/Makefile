##
## EPITECH PROJECT, 2026
## 42sh
## File description:
## instaler/Makefile
##

MAKEFLAGS += --no-print-directory

# ─── Project Info ────────────────────────────────────────────────────────
PROJECT  = instaler
NAME     = instaler

# ─── Sources ─────────────────────────────────────────────────────────────
SRC = \
	src/main.c \
	src/init/init.c

OBJ = $(SRC:.c=.o)

# ─── Flags ───────────────────────────────────────────────────────────────
WFLAGS  = -Wall -Wextra -Werror -Wshadow -Wno-unused-parameter
CFLAGS  = -Iinclude $(WFLAGS)
LDFLAGS = -lncurses

# ─── Tools ───────────────────────────────────────────────────────────────
RM  = rm -rf
ECC = epiclang

# ─── Per-file compilation ─────────────────────────────────────────────────
%.o: %.c
	@printf "$(H_CYAN)Compiling$(END) $(BOLD)$<$(END) ...\n"
	@$(ECC) $(CFLAGS) -Wno-unused-command-line-argument -c $< -o $@ && \
		printf "%b\n" "$(BOLD)$(H_GREEN)[ OK ]$(END)" || \
		(printf "%b\n" "$(BOLD)$(H_RED)[ FAIL ]$(END)" && $(ECC) $(CFLAGS) -c $< -o $@ && exit 1)

# ─── Macro: Fancy Header ─────────────────────────────────────────────────
define pretty_header
	@printf "%b\n" "$(BOLD)$(H_PURPLE)╔═══════════════════════════════════════════════════════════════╗$(END)"
	@printf "%b\n" "$(BOLD)$(H_PURPLE)║$(END)$(BOLD)$(WHITE) $(1)$(END)"
	@printf "%b\n" "$(BOLD)$(H_PURPLE)╚═══════════════════════════════════════════════════════════════╝$(END)"
endef

# ─── Rules ───────────────────────────────────────────────────────────────
.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	@echo ""
	$(call pretty_header, Creating binary of : $(PROJECT))
	@$(ECC) $(CFLAGS) -Wno-unused-command-line-argument -o $(NAME) $(OBJ) $(LDFLAGS)
	@printf "%b\n" "$(BOLD)$(WHITE) done$(END)"
	$(call pretty_header, Successfully compiled $(PROJECT)!)
	@echo ""

clean:
	$(call pretty_header, Cleaning object files)
	@$(RM) $(OBJ)

fclean: clean
	$(call pretty_header, Full clean)
	@$(RM) $(NAME)

re: fclean all

# ─── Styles ──────────────────────────────────────────────────────────────
END     = \033[0m
BOLD    = \033[1m

# ─── Colors ──────────────────────────────────────────────────────────────
WHITE    = \033[37m
H_RED    = \033[91m
H_GREEN  = \033[92m
H_PURPLE = \033[95m
H_CYAN   = \033[96m
