##
## EPITECH PROJECT, 2026
## 42sh
## File description:
## Makefile — see "make help"
##

MAKEFLAGS += --no-print-directory

# ─── Project Info ────────────────────────────────────────────────────────
PROJECT  = 42sh
NAME     = 42sh

# ─── Sources ─────────────────────────────────────────────────────────────
SRC_CORE = \
	src/core/main.c \
	src/core/init/init_env.c \
	src/core/init/init_main.c \
	src/core/context/command_context.c

SRC_BUILTINS = \
	src/builtins/env/my_env.c \
	src/builtins/env/my_setenv.c \
	src/builtins/env/my_unsetenv.c \
	src/builtins/fs/my_chdir.c \
	src/builtins/jobs/my_jobs.c \
	src/builtins/jobs/my_foreground.c \
	src/builtins/jobs/my_background.c \
	src/builtins/repeat/repeat.c

SRC_EXEC = \
	src/execution/dispatch/execute_builtin.c \
	src/execution/dispatch/execute_command.c \
	src/execution/dispatch/execute_single_command.c \
	src/execution/external/exec_any.c \
	src/execution/external/exec_error_case.c \
	src/execution/external/run_fork.c \
	src/execution/pipeline/pipeline_execute.c \
	src/execution/pipeline/pipeline_parse.c \
	src/execution/pipeline/pipeline_spawn.c \
	src/execution/pipeline/pipeline_syntax.c \
	src/execution/pipeline/pipeline_wait.c \
	src/execution/redirection/apply_redirection.c

SRC_ENV = \
	src/environment/path/check_bin.c \
	src/environment/query/get_home.c \
	src/environment/query/get_path.c

SRC_PARSING = \
	src/parsing/redirection/get_redirection.c

SRC_UTILS = \
	src/utils/io/my_putstr.c \
	src/utils/io/get_file_size_stat.c \
	src/utils/io/openator.c \
	src/utils/display/get_branch_git.c \
	src/utils/display/get_folder.c \
	src/utils/display/prompt.c \
	src/utils/strings/my_strcmp.c \
	src/utils/strings/my_strconcat.c \
	src/utils/strings/my_strdup.c \
	src/utils/strings/my_strlen.c \
	src/utils/strings/my_strncmp.c \
	src/utils/strings/my_strstr.c \
	src/utils/strings/my_str_to_word_array.c \
	src/utils/strings/my_wordarraylen.c \
	src/utils/validation/my_ischar_num.c \
	src/utils/validation/my_str_is_alphanum.c

SRC_MEMORY = \
	src/memory/free/free_function.c

SRC = \
	$(SRC_CORE) \
	$(SRC_BUILTINS) \
	$(SRC_EXEC) \
	$(SRC_ENV) \
	$(SRC_PARSING) \
	$(SRC_UTILS) \
	$(SRC_MEMORY)

OBJ = $(SRC:.c=.o)

# ─── Flags ───────────────────────────────────────────────────────────────
WFLAGS      = -Wall -Wextra -Werror -Wshadow -Wno-unused-parameter
CFLAGS      = -Iinclude $(WFLAGS)
DEBUGFLAGS  = -Iinclude -g3 -Wshadow -Wno-unused-parameter
GCOVRSTYLE  = 'github.dark-green'
LOGS_DIR    = Logs
COVERAGE_DIR  = $(LOGS_DIR)/coverage
COVERAGE_HTML = $(COVERAGE_DIR)/index.html
WEBGCOVRFLAGS = --html-theme $(GCOVRSTYLE) --html --html-nested -o $(COVERAGE_HTML)
GCOVRFLAGS  = --gcov-executable "llvm-cov-20 gcov" --exclude tests/

# ─── Tools ───────────────────────────────────────────────────────────────
RM           = rm -rf
ECC          = epiclang
ARGUMENTS    =
DEBUG_STRICT ?= 0
LOCAL_BIN   ?= $(HOME)/.local/bin

# ─── Misc ────────────────────────────────────────────────────────────────
TO_RM = *.gcda *.gcno unit_tests *.html *.css *.log $(LOGS_DIR)

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
.PHONY: all re clean fclean \
        install uninstall \
        debug debug_build valgrind \
        unit_tests tests_run coverage functional_tests \
        help

all: $(NAME)

$(NAME): $(OBJ)
	@echo ""
	$(call pretty_header, Creating binary of : $(PROJECT))
	@$(ECC) $(CFLAGS) -Wno-unused-command-line-argument -o $(NAME) $(OBJ)
	@printf "%b\n" "$(BOLD)$(WHITE) done$(END)"
	$(call pretty_header, Successfully compiled $(PROJECT)!)
	@echo ""

install: $(NAME)
	@mkdir -p $(LOCAL_BIN)
	@cp $(NAME) $(LOCAL_BIN)/$(NAME)
	@chmod u+x $(LOCAL_BIN)/$(NAME)
	@printf "%b\n" "$(BOLD)$(H_GREEN)Installed$(END) $(NAME) -> $(LOCAL_BIN)/$(NAME)"
	@if ! printf "%b\n" "$$PATH" | grep -q "$(LOCAL_BIN)"; then \
		printf "%b\n" "$(BOLD)$(H_YELLOW)$(LOCAL_BIN) is not in PATH.$(END)"; \
		printf "%b\n" "Add this to ~/.zshrc:"; \
		printf "%b\n" "  export PATH=\"$(LOCAL_BIN):\$$PATH\""; \
		printf "%b\n" "Then run: source ~/.zshrc && hash -r"; \
	fi

uninstall:
	@rm -f $(LOCAL_BIN)/$(NAME)
	@printf "%b\n" "$(BOLD)$(H_YELLOW)Removed$(END) $(LOCAL_BIN)/$(NAME)"

debug: debug_build valgrind

debug_build:
	$(call pretty_header, Compiling with debug flag for : $(PROJECT))
	@$(ECC) $(DEBUGFLAGS) -Wno-unused-command-line-argument -o $(NAME) $(SRC)
	@printf "%b\n" "$(BOLD)$(WHITE) done$(END)"
	@echo ""
	@printf "%b\n" "$(BOLD)$(H_GREEN)Debug build ready! Time to hunt bugs!$(END)"
	@printf "%b\n" "$(H_CYAN)Tip: set DEBUG_STRICT=1 to make valgrind fail the target$(END)"

valgrind:
	@echo ""
	@printf "%b\n" "$(H_PURPLE)Running Valgrind memory check...$(END)"
	@mkdir -p $(LOGS_DIR)
	@VALGRIND_STATUS=0; \
	valgrind --leak-check=full \
	    --show-leak-kinds=all \
	    --track-origins=yes \
	    --log-file=$(LOGS_DIR)/valgrind.log \
	    ./$(NAME) $(ARGUMENTS) || VALGRIND_STATUS=$$?; \
	printf "%b\n" "$(H_CYAN)Valgrind report saved to $(H_YELLOW)$(LOGS_DIR)/valgrind.log$(END)"; \
	printf "%b\n" ""; \
	if [ -f $(LOGS_DIR)/valgrind.log ] && grep -q "ERROR SUMMARY: 0 errors" $(LOGS_DIR)/valgrind.log; then \
	    printf "%b\n" "$(BOLD)$(H_GREEN)No memory errors detected! Perfect!$(END)"; \
	else \
	    printf "%b\n" "$(BOLD)$(H_YELLOW)Memory issues detected. Check $(LOGS_DIR)/valgrind.log$(END)"; \
	fi; \
	if [ "$(DEBUG_STRICT)" = "1" ] && [ $$VALGRIND_STATUS -ne 0 ]; then exit $$VALGRIND_STATUS; fi
	@echo ""

unit_tests: re
	@$(MAKE) -C tests unit_tests

tests_run: re
	@$(MAKE) -C tests tests_run

coverage: re
	@$(MAKE) -C tests coverage src/execution/redirection/apply_redirection.c
functional_tests: all
	$(call pretty_header, Running Functional Tests)
	@mkdir -p $(LOGS_DIR)/functional_tests
	@./tests/run_tests.sh; EXIT_CODE=$$?; \
	echo" ""; \
	printf "%b\n" "$(H_CYAN)Functional test report saved to $(H_YELLOW)$(LOGS_DIR)/functional_tests/$(END)"; \
	if [ $$EXIT_CODE -eq 0 ]; then \
	    printf "%b\n" "$(BOLD)$(H_GREEN)All functional tests passed!$(END)"; \
	else \
	    printf "%b\n" "$(BOLD)$(H_YELLOW)Some tests failed! Check $(LOGS_DIR)/functional_tests/ for details$(END)"; \
	fi; \
	exit $$EXIT_CODE

clean:
	$(call pretty_header, Cleaning object files)
	@$(RM) $(OBJ)
	@$(MAKE) clean -C tests/

fclean: clean
	$(call pretty_header, Full clean: objects binary tests coverage)
	@$(RM) $(NAME) $(TO_RM)
	@$(MAKE) fclean -C tests/

re: fclean all

# ─── Help ────────────────────────────────────────────────────────────────
help:
	@echo ""
	@printf "%b\n" "$(BOLD)$(H_PURPLE)╔═══════════════════════════════════════════════════════════════╗$(END)"
	@printf "%b\n" "$(BOLD)$(H_PURPLE)║$(END)$(BOLD)$(H_WHITE)   42sh — Unix Shell in C  ·  Help Menu                       $(H_PURPLE)║$(END)"
	@printf "%b\n" "$(BOLD)$(H_PURPLE)╚═══════════════════════════════════════════════════════════════╝$(END)"
	@echo ""
	@printf "%b\n" "$(BOLD)$(H_CYAN)── Build ─────────────────────────────────────────────────────────$(END)"
	@printf "%b\n" "  $(BOLD)make$(END) / $(BOLD)make all$(END)             Compile all sources from src/ into $(BOLD)$(NAME)$(END)"
	@printf "%b\n" "  $(BOLD)make re$(END)                     Full rebuild (fclean + all)"
	@printf "%b\n" "  $(BOLD)make debug$(END)                  Debug build (-g3) + Valgrind memory report"
	@printf "%b\n" "  $(BOLD)make debug DEBUG_STRICT=1$(END)   Fail target if Valgrind returns non-zero"
	@printf "%b\n" "  $(BOLD)make valgrind$(END)               Run Valgrind on current binary"
	@echo ""
	@printf "%b\n" "$(BOLD)$(H_CYAN)── Install ───────────────────────────────────────────────────────$(END)"
	@printf "%b\n" "  $(BOLD)make install$(END)                Install $(NAME) to $(LOCAL_BIN)"
	@printf "%b\n" "  $(BOLD)make uninstall$(END)              Remove $(NAME) from $(LOCAL_BIN)"
	@echo ""
	@printf "%b\n" "$(BOLD)$(H_CYAN)── Tests & Coverage ──────────────────────────────────────────────$(END)"
	@printf "%b\n" "  $(BOLD)make unit_tests$(END)             Build Criterion unit-tests binary"
	@printf "%b\n" "  $(BOLD)make tests_run$(END)              Run tests → logs in $(LOGS_DIR)/"
	@printf "%b\n" "  $(BOLD)make coverage$(END)               Run tests → HTML report at $(COVERAGE_HTML)"
	@printf "%b\n" "  $(BOLD)make functional_tests$(END)       Run functional tests (tests/run_tests.sh)"
	@printf "%b\n" ""
	@printf "%b\n" "$(BOLD)$(H_CYAN)── Cleanup ───────────────────────────────────────────────────────$(END)"
	@printf "%b\n" "  $(BOLD)make clean$(END)                  Remove .o files"
	@printf "%b\n" "  $(BOLD)make fclean$(END)                 Remove binary, tests and coverage artifacts"
	@printf "%b\n" ""
	@printf "%b\n" "$(BOLD)$(H_CYAN)── Variables ─────────────────────────────────────────────────────$(END)"
	@printf "%b\n" "  ARGUMENTS    = $(ARGUMENTS)"
	@printf "%b\n" "  DEBUG_STRICT = $(DEBUG_STRICT)"
	@printf "%b\n" "  LOCAL_BIN    = $(LOCAL_BIN)"
	@echo ""

# ─── Styles ──────────────────────────────────────────────────────────────
END     = \033[0m
BOLD    = \033[1m
ITALICS = \033[3m
UNDER   = \033[4m
REV     = \033[7m

# ─── Colors ──────────────────────────────────────────────────────────────
GREY    = \033[30m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
PURPLE  = \033[35m
CYAN    = \033[36m
WHITE   = \033[37m
H_GREY   = \033[90m
H_RED    = \033[91m
H_GREEN  = \033[92m
H_YELLOW = \033[93m
H_BLUE   = \033[94m
H_PURPLE = \033[95m
H_CYAN   = \033[96m
H_WHITE  = \033[97m

# ─── Background ──────────────────────────────────────────────────────────
B_GREY   = \033[40m
B_RED    = \033[41m
B_GREEN  = \033[42m
B_YELLOW = \033[43m
B_BLUE   = \033[44m
B_PURPLE = \033[45m
B_CYAN   = \033[46m
B_WHITE  = \033[47m
HB_GREY   = \033[100m
HB_RED    = \033[101m
HB_GREEN  = \033[102m
HB_YELLOW = \033[103m
HB_BLUE   = \033[104m
HB_PURPLE = \033[105m
HB_CYAN   = \033[106m
HB_WHITE  = \033[107m
