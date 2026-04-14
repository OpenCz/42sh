##
## EPITECH PROJECT, 2026
## 42sh — tests/Makefile
## File description:
## Dedicated Makefile for Criterion unit tests and functional tests
##

MAKEFLAGS += --no-print-directory

# ─── Test sources ─────────────────────────────────────────────────────────
SRC_TESTS = \
	test_minishell_unit.c

# ─── Project sources (no main.c) ─────────────────────────────────────────
SRC_CORE = \
	../src/core/init/init_env.c \
	../src/core/init/init_main.c \
	../src/core/context/command_context.c

SRC_BUILTINS = \
	../src/builtins/env/my_env.c \
	../src/builtins/env/my_setenv.c \
	../src/builtins/env/my_unsetenv.c \
	../src/builtins/fs/my_chdir.c \
	../src/builtins/jobs/my_jobs.c \
	../src/builtins/jobs/my_foreground.c \
	../src/builtins/jobs/my_background.c \
	../src/builtins/repeat/repeat.c

SRC_EXEC = \
	../src/execution/dispatch/execute_builtin.c \
	../src/execution/dispatch/execute_command.c \
	../src/execution/dispatch/execute_single_command.c \
	../src/execution/external/exec_any.c \
	../src/execution/external/exec_error_case.c \
	../src/execution/external/run_fork.c \
	../src/execution/pipeline/pipeline_execute.c \
	../src/execution/pipeline/pipeline_parse.c \
	../src/execution/pipeline/pipeline_spawn.c \
	../src/execution/pipeline/pipeline_syntax.c \
	../src/execution/pipeline/pipeline_wait.c \
	../src/execution/redirection/apply_redirection.c

SRC_ENV = \
	../src/environment/path/check_bin.c \
	../src/environment/query/get_home.c \
	../src/environment/query/get_path.c

SRC_PARSING = \
	../src/parsing/redirection/get_redirection.c

SRC_UTILS = \
	../src/utils/io/my_putstr.c \
	../src/utils/strings/my_strcmp.c \
	../src/utils/strings/my_strconcat.c \
	../src/utils/strings/my_strdup.c \
	../src/utils/strings/my_strlen.c \
	../src/utils/strings/my_strncmp.c \
	../src/utils/strings/my_strstr.c \
	../src/utils/strings/my_str_to_word_array.c \
	../src/utils/strings/my_wordarraylen.c \
	../src/utils/validation/my_ischar_num.c \
	../src/utils/validation/my_str_is_alphanum.c

SRC_MEMORY = \
	../src/memory/free/free_function.c

SRC_PROJECT = \
	$(SRC_CORE) \
	$(SRC_BUILTINS) \
	$(SRC_EXEC) \
	$(SRC_ENV) \
	$(SRC_PARSING) \
	$(SRC_UTILS) \
	$(SRC_MEMORY)

SRCTST = $(SRC_TESTS) $(SRC_PROJECT)

# ─── Flags ───────────────────────────────────────────────────────────────
CC          = clang
RM          = rm -rf
TESTSFLAGS  = --coverage -lcriterion
CFLAGS      = -I../include -Wall -Wextra -Wshadow -Wno-unused-parameter
GCOVRSTYLE  = 'github.dark-green'
LOGS_DIR    = ../Logs
COVERAGE_DIR     = $(LOGS_DIR)/coverage
COVERAGE_RAW_DIR = $(COVERAGE_DIR)/raw
COVERAGE_HTML    = $(COVERAGE_DIR)/index.html
WEBGCOVRFLAGS    = --html-theme $(GCOVRSTYLE) --html --html-nested -o $(COVERAGE_HTML)
GCOVRFLAGS  = --gcov-executable "llvm-cov-20 gcov" --exclude tests/ --root ..
VALGRIND_LOG  = $(LOGS_DIR)/valgrind.log
VALGRIND_HTML = $(LOGS_DIR)/valgrind.html

# ─── Colors ──────────────────────────────────────────────────────────────
END      = \033[0m
BOLD     = \033[1m
H_GREEN  = \033[92m
H_YELLOW = \033[93m
H_CYAN   = \033[96m

# ─── Rules ───────────────────────────────────────────────────────────────
.PHONY: all unit_tests tests_run coverage clean fclean

all: unit_tests

unit_tests:
	@mkdir -p $(LOGS_DIR) $(COVERAGE_RAW_DIR)
	@printf "$(H_CYAN)Building$(END) $(BOLD)unit_tests$(END) ...\n"
	@$(CC) -o unit_tests $(SRCTST) $(TESTSFLAGS) $(CFLAGS) && \
		printf "%b\n" "$(BOLD)$(H_GREEN)[ OK ]$(END)" || \
		(printf "%b\n" "$(BOLD)$(H_YELLOW)[ FAIL ]$(END)" && exit 1)

tests_run: unit_tests
	@CRITERION_SHOW_STDOUT=1 ./unit_tests > $(LOGS_DIR)/test_output.log 2>&1; EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
	    printf "%b\n" "$(BOLD)$(H_YELLOW)Some tests failed! Check $(LOGS_DIR)/test_output.log$(END)"; \
	    cat $(LOGS_DIR)/test_output.log; \
	    exit $$EXIT_CODE; \
	fi; \
	printf "%b\n" "$(BOLD)$(H_GREEN)All tests passed! Generating coverage report...$(END)"; \
	gcovr $(GCOVRFLAGS) $(WEBGCOVRFLAGS) > $(LOGS_DIR)/coverage_report.log 2>&1; \
	gcovr $(GCOVRFLAGS) --branches >> $(LOGS_DIR)/coverage_report.log 2>&1; \
	printf "%b\n" "$(BOLD)$(H_GREEN)Done! Logs: $(LOGS_DIR)/test_output.log | $(LOGS_DIR)/coverage_report.log$(END)"

coverage: unit_tests
	@mkdir -p $(LOGS_DIR) $(COVERAGE_RAW_DIR)
	@./unit_tests
	@gcovr $(GCOVRFLAGS) $(WEBGCOVRFLAGS)
	@gcovr $(GCOVRFLAGS) --txt-metric branch
	@printf "%b\n" "$(BOLD)$(H_CYAN)Running Valgrind...$(END)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	    --log-file=$(VALGRIND_LOG) ./unit_tests 2>/dev/null; \
	{ echo '<!DOCTYPE html><html><head><meta charset="utf-8">'; \
	  echo '<title>Valgrind Report</title>'; \
	  echo '<style>'; \
	  echo 'body{background:#0d1117;color:#e6edf3;font-family:monospace;padding:2em;margin:0}'; \
	  echo 'h1{color:#58a6ff;border-bottom:1px solid #30363d;padding-bottom:.5em}'; \
	  echo 'pre{white-space:pre-wrap;background:#161b22;padding:1.5em;border-radius:6px;'; \
	  echo '    border:1px solid #30363d;overflow-x:auto}'; \
	  echo '</style></head><body>'; \
	  echo '<h1>Valgrind Report — unit_tests</h1><pre>'; \
	  cat $(VALGRIND_LOG); \
	  echo '</pre></body></html>'; } > $(VALGRIND_HTML)
	@printf "%b\n" "$(BOLD)$(H_GREEN)Valgrind report: $(VALGRIND_HTML)$(END)"
	@xdg-open $(COVERAGE_HTML)
	@xdg-open $(VALGRIND_HTML)

clean:
	@$(RM) unit_tests *.gcda *.gcno

fclean: clean