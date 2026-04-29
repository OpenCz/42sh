# Project Architecture

This document describes the current architecture of 42sh and the design
rules that keep the codebase modular, readable, and easy to evolve.

## 1. Big Picture

The project is split by business responsibility:

- `src/core`: global shell lifecycle, REPL loop, interactive input, signal setup.
- `src/builtins`: internal commands (`env`, `setenv`, `cd`, `foreach`, `repeat`, `history`, `source`, …).
- `src/execution`: execution orchestration (dispatch, external fork/exec, pipeline, redirections).
- `src/environment`: environment access and binary resolution through PATH.
- `src/parsing`: tokenization, quote handling, `$VAR` substitution, redirection detection.
- `src/config`: RC file loading and prompt configuration.
- `src/utils`: low-level utility functions (string, io, display, validation).
- `src/memory`: destruction and cleanup of dynamic structures.

The `include` directory mirrors this layout, with public APIs separated by domain.

---

## 2. Detailed Layout

### 2.1 Core

- `src/core/main.c`: REPL loop entry point; owns `loop_state_t`, calls `get_command` and `execute_command`.
- `src/core/init/init_env.c`: build the `env_t` environment linked list from `environ`.
- `src/core/init/init_main.c`: initialize the global `main_t` state (PATH, HOME, history).
- `src/core/context/get_command.c`: interactive input loop — raw termios, character-by-character reading, returns a complete line.
- `src/core/context/command_context.c`: parse a raw command string into `command_ctx_t`.
- `src/core/context/key_binding.c`: handlers for Ctrl+C (clear line), Ctrl+D (EOF), Ctrl+L (clear screen).
- `src/core/context/arrow_handling.c`: escape sequences for arrow key navigation.
- `src/core/context/manage_history.c`: push/load/navigate history linked list; read/write `~/.c_zsh_history`.
- `src/core/context/termios.c`: enable/disable raw terminal mode (`ICANON`, `ECHO`).
- `src/core/context/signal.c`: `setup_shell_signals()` — shell ignores `SIGINT`, `SIGTSTP`, `SIGTTOU`, `SIGTTIN`, `SIGQUIT`; sets process group.
- `src/core/context/display.c`: in-line display helpers (cursor movement, line redraw).
- `src/core/context/tab.c`: tab completion handler (stub).

### 2.2 Builtins

- `src/builtins/env/my_env.c`: display the full environment.
- `src/builtins/env/my_setenv.c`: add or update an environment variable.
- `src/builtins/env/my_unsetenv.c`: remove an environment variable.
- `src/builtins/env/printenv.c`: print a single environment variable.
- `src/builtins/fs/my_chdir.c`: `cd` — change directory, handle `~`, `-`, update `PWD`/`OLDPWD`.
- `src/builtins/fs/my_which.c`: `which` — first binary match in PATH.
- `src/builtins/fs/my_where.c`: `where` — all binary matches in PATH.
- `src/builtins/jobs/my_jobs.c`: `jobs` (stub).
- `src/builtins/jobs/my_foreground.c`: `fg` (stub).
- `src/builtins/jobs/my_background.c`: `bg` (stub).
- `src/builtins/repeat/repeat.c`: `repeat N cmd` — execute a command N times.
- `src/builtins/scripts/foreach.c`: `foreach var (items) … end` — outer iteration loop.
- `src/builtins/scripts/foreach_input.c`: input reading for `foreach` body.
- `src/builtins/history/history.c`: `history` — display numbered history with timestamps.
- `src/builtins/config/source.c`: `source` / `.` — execute commands from a file.

### 2.3 Execution

- `src/execution/dispatch/execute_command.c`: split input by `;`, dispatch each sub-command.
- `src/execution/dispatch/execute_single_command.c`: non-pipeline path — parse context, try builtin, fall back to external.
- `src/execution/dispatch/execute_operation.c`: evaluate `&&` / `||` operator chains.
- `src/execution/dispatch/execute_builtin.c`: builtin registry (`builtin_command_t[]`) and linear-search dispatch.
- `src/execution/external/exec_any.c`: command resolution and external launch entry point.
- `src/execution/external/run_fork.c`: `fork` + terminal handoff + `waitpid(WUNTRACED)` + status normalization.
- `src/execution/external/exec_error_case.c`: `execve` error handling; signal-to-exit-code mapping (`SIGINT`→130, `SIGSEGV`→139, `SIGFPE`→136, `WIFSTOPPED`→print "Suspended").
- `src/execution/pipeline/pipeline_parse.c`: split on `|` into `pipeline_segment_t[]`.
- `src/execution/pipeline/pipeline_spawn.c`: fork each segment with pipe FD wiring.
- `src/execution/pipeline/pipeline_wait.c`: `waitpid` all PIDs, return last segment status.
- `src/execution/pipeline/pipeline_execute.c`: orchestrate parse → spawn → wait → cleanup.
- `src/execution/pipeline/pipeline_syntax.c`: syntax validation (no empty segments).
- `src/execution/redirection/apply_redirection.c`: detect token, open file, `dup2`, truncate `argv`.

### 2.4 Config

- `src/config/czshrc.c`: load and parse the `.c_zshrc` configuration file.
- `src/config/manage_prompt.c`: parse prompt configuration into `czshrc_t`.
- `src/config/set_default_rc.c`: apply built-in defaults when no RC file is found.

### 2.5 Environment

- `src/environment/query/get_home.c`: read `HOME`.
- `src/environment/query/get_path.c`: read and split `PATH`.
- `src/environment/query/get_user.c`: read `USER`.
- `src/environment/path/check_bin.c`: executable resolution through PATH entries.

### 2.6 Parsing

- `src/parsing/redirection/get_redirection.c`: detect `>>`, `<<`, `>`, `<` tokens.
- `src/parsing/quotes_management/manage_quotes.c`: remove outer double quotes; interpret escape sequences (`\n`, `\t`, `\\`, `\"`, …).
- `src/parsing/env_var_management/replace_env_vars.c`: `$VAR` / `${VAR}` substitution in each `argv` token.

### 2.7 Utils

- `src/utils/strings/*`: custom string helpers (`strlen`, `strdup`, `strcmp`, `strconcat`, `strstr`, word-array builders).
- `src/utils/io/my_putstr.c`: write to stdout / stderr.
- `src/utils/display/prompt.c`: styled prompt rendering (colors, directory, git branch).
- `src/utils/display/get_branch_git.c`: current git branch detection.
- `src/utils/display/display_time.c`: timestamp formatting for history.
- `src/utils/validation/*`: character-class helpers (`isalpha`, `isnum`, `isalphanum`).

### 2.8 Memory

- `src/memory/free/free_function.c`: `free_alloc`, `free_array`, `free_linked_list`, `free_history`, `free_main`.

---

## 3. Core Types

All central types are declared in `include/core/types.h`:

| Type | Description |
|---|---|
| `env_t` | Singly-linked `key/value` node for the environment. |
| `main_t` | Long-lived global shell state: env list, PATH, HOME, history, RC config. |
| `command_ctx_t` | Ephemeral context for one command: `command`, `argv`, `arg_command`, `redirection`. |
| `pipeline_segment_t` | One `\|`-separated command with its own `argv`. |
| `pipeline_state_t` | Full pipeline execution context: segments, pipe FDs, child PIDs, count. |
| `loop_state_t` | REPL iteration state: input buffer, last exit code, prompt-displayed flag. |
| `history_cmd_t` | Doubly-linked history node: `id`, `cmd`, `prev`, `next`. |
| `history_t` | History head pointer, current navigation cursor, auto-increment ID, saved input. |
| `czshrc_t` | RC configuration, owns `prompt_t` (colors, format string). |

---

## 4. Modular Boundaries

Key modularity rules:

- `dispatch` modules do not contain business logic for redirections or builtins.
- `external` modules do not parse commands; they consume an already valid `command_ctx_t`.
- Builtins are invoked exclusively through the registry (`builtin_command_t[]`) with a uniform signature.
- Redirection parsing is isolated from fork/exec code.
- The pipeline is handled as an independent unit with its own `pipeline_state_t`.
- Signal setup is confined to `signal.c`; signal-to-exit-code mapping is in `exec_error_case.c`.
- RC and prompt configuration is confined to `src/config/`; no other module reads the RC file.

---

## 5. Execution Flow (summary)

Nominal path for a single command:

1. `main` reads a line (interactive: raw termios loop; non-interactive: `getline`).
2. `execute_command` splits the line on `;`.
3. Each segment is routed: pipeline → `execute_pipeline`; operators → `execute_operator`; plain → `execute_single_command`.
4. `execute_single_command` parses `command_ctx_t` and runs `$VAR` substitution.
5. If the command is in the builtin registry: execute the handler.
6. Otherwise: `exec_any` → `check_bin` → `run_fork` → child `execve`.
7. Parent `waitpid(WUNTRACED)`: detect exit, signal, or stop (Ctrl+Z).
8. Status is returned up the call chain to the REPL.

See `docs/EXECUTION_FLOW.md` for the full step-by-step walk-through and
`docs/ARCHITECTURE_DIAGRAM.mmd` for a visual flowchart of all loops.

---

## 6. Header APIs by Domain

Public entry points are separated:

- `include/core/core.h`
- `include/builtins/builtins.h`
- `include/execution/execution.h`
- `include/environment/environment.h`
- `include/parsing/parsing.h`
- `include/utils/utils.h`
- `include/memory/memory.h`

The `include/c_zsh.h` file acts as an aggregator facade that includes all domain headers.

---

## 7. Recommended Evolution

To remain modular over time:

- Add each new feature in an existing or new subdomain, never in a catch-all file.
- Keep functions `static` when they are not exported in a domain header.
- Separate parsing, validation, and execution into distinct functions.
- Add at least one unit test for every new critical code path.
- Document any new structure in this file and in `include/core/types.h`.

---

## 8. Pre-merge Checklist

- The module has a clear domain (`core`, `execution`, `builtins`, etc.).
- The header exports only what is necessary.
- The code does not depend on a global field when a local context suffices.
- Every allocation has an explicit destructor path.
- `make re` and `make unit_tests` pass without warnings.
