##
## EPITECH PROJECT, 2026
## 42sh — tests/Makefile
## File description:
## Dedicated Makefile for Criterion unit tests and functional tests
##

MAKEFLAGS += --no-print-directory

# ─── Test sources ─────────────────────────────────────────────────────────
SRC_TESTS = $(wildcard test_*.c)

# ─── Project sources (no main.c) ─────────────────────────────────────────
SRC_CORE = \
	$(wildcard ../src/core/init/*.c) \
	$(wildcard ../src/core/context/*.c)

SRC_BUILTINS = \
	$(wildcard ../src/builtins/env/*.c) \
	$(wildcard ../src/builtins/fs/*.c) \
	$(wildcard ../src/builtins/jobs/*.c) \
	$(wildcard ../src/builtins/repeat/*.c) \
	$(wildcard ../src/builtins/history/*.c)

SRC_EXEC = \
	$(wildcard ../src/execution/dispatch/*.c) \
	$(wildcard ../src/execution/external/*.c) \
	$(wildcard ../src/execution/pipeline/*.c) \
	$(wildcard ../src/execution/redirection/*.c)

SRC_ENV = \
	$(wildcard ../src/environment/path/*.c) \
	$(wildcard ../src/environment/query/*.c)

SRC_PARSING = \
	$(wildcard ../src/parsing/redirection/*.c) \
	$(wildcard ../src/parsing/env_var_management/*.c) \
	$(wildcard ../src/parsing/quotes_management/*.c)

SRC_UTILS = \
	$(wildcard ../src/utils/io/*.c) \
	$(wildcard ../src/utils/strings/*.c) \
	$(wildcard ../src/utils/validation/*.c) \
	$(wildcard ../src/utils/display/*.c)

SRC_MEMORY = \
	$(wildcard ../src/memory/free/*.c)

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
WEBGCOVRFLAGS    = --html-theme $(GCOVRSTYLE) --html -o $(COVERAGE_HTML)
GCOVRFLAGS  = --gcov-executable "llvm-cov-20 gcov" --filter ".*src/.*" --exclude ".*tests/.*" --exclude-directories "tests" --root ..
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
	@mkdir -p $(LOGS_DIR) $(COVERAGE_DIR) $(COVERAGE_RAW_DIR)
	@CRITERION_SHOW_STDOUT=1 ./unit_tests > $(LOGS_DIR)/test_output.log 2>&1; EXIT_CODE=$$?; \
	if [ $$EXIT_CODE -ne 0 ]; then \
	    printf "%b\n" "$(BOLD)$(H_YELLOW)Some tests failed! Check $(LOGS_DIR)/test_output.log$(END)"; \
	    cat $(LOGS_DIR)/test_output.log; \
	    exit $$EXIT_CODE; \
	fi
	@printf "%b\n" "$(BOLD)$(H_GREEN)All tests passed! Generating coverage report...$(END)"
	@gcovr $(GCOVRFLAGS) $(WEBGCOVRFLAGS) > $(LOGS_DIR)/coverage_report.log 2>&1
	@gcovr $(GCOVRFLAGS) --txt-metric branch >> $(LOGS_DIR)/coverage_report.log 2>&1
	@printf "%b\n" "$(BOLD)$(H_CYAN)Running Valgrind...$(END)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	    --log-file=$(VALGRIND_LOG) ./unit_tests >/dev/null 2>&1; \
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
	@printf "%b\n" "$(BOLD)$(H_GREEN)Done! Logs: $(LOGS_DIR)/test_output.log | $(LOGS_DIR)/coverage_report.log$(END)"
	@printf "%b\n" "$(BOLD)$(H_GREEN)Reports: $(COVERAGE_HTML) | $(VALGRIND_HTML)$(END)"
	@if command -v xdg-open >/dev/null 2>&1; then \
		xdg-open $(COVERAGE_HTML) >/dev/null 2>&1 || true; \
		xdg-open $(VALGRIND_HTML) >/dev/null 2>&1 || true; \
	fi

clean:
	@$(RM) unit_tests *.gcda *.gcno

fclean: clean
