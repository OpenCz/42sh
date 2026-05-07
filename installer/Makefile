##
## EPITECH PROJECT, 2026
## 42sh
## File description:
## instaler/Makefile
##

MAKEFLAGS += --no-print-directory

# ─── Project Info ────────────────────────────────────────────────────────
PROJECT  = install
NAME     = install

# ─── Sources ─────────────────────────────────────────────────────────────
SRC = \
	src/core/main.c \
	src/init/init.c \
	src/core/loop/loop.c \
	src/utils/io/openator.c \
	src/utils/io/get_file_size_stat.c \
	src/utils/memory/free_function.c \
	src/utils/string/str_to_array_of_word_array.c \
	src/utils/string/my_str_to_word_array.c \
	src/display/print_ascii.c \
	src/init/closup.c \
	src/install/detect_os.c \
	src/install/preferences.c \
	src/install/render.c \
	src/install/render_alias_edit.c \
	src/install/inputs.c \
	src/install/inputs_alias_edit.c \
	src/install/write_rc.c \

OBJ = $(SRC:.c=.o)

# ─── Flags ───────────────────────────────────────────────────────────────
WFLAGS  = -Wall -Wextra 
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
.PHONY: all re clean fclean installer

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

installer: all
	$(call pretty_header, Detecting OS and installing 42SH rc)
	@OS_ID=""; \
	if [ -f /etc/os-release ]; then \
		OS_ID=$$(. /etc/os-release 2>/dev/null && echo $$ID); \
	elif [ "$$(uname -s)" = "Darwin" ]; then \
		OS_ID="macos"; \
	else \
		OS_ID="unknown"; \
	fi; \
	printf "$(BOLD) OS detected: $$OS_ID$(END)\n"; \
	if [ "$$OS_ID" = "nixos" ]; then \
		RC_DIR="$$HOME/.config/42sh"; \
		mkdir -p "$$RC_DIR"; \
		RC_PATH="$$RC_DIR/rc"; \
	else \
		RC_PATH="$$HOME/.42shrc"; \
	fi; \
	cp assets/42shrc "$$RC_PATH" && \
		printf "$(BOLD)$(H_GREEN) Placed rc → $$RC_PATH$(END)\n" || \
		printf "$(BOLD)$(H_RED) Failed to place rc$(END)\n"
	$(call pretty_header, Launching installer)
	@./$(NAME)

# ─── Styles ──────────────────────────────────────────────────────────────
END     = \033[0m
BOLD    = \033[1m

# ─── Colors ──────────────────────────────────────────────────────────────
WHITE    = \033[37m
H_RED    = \033[91m
H_GREEN  = \033[92m
H_PURPLE = \033[95m
H_CYAN   = \033[96m
