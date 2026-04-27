# Project Architecture

This document describes the current architecture of the minishell and the design
rules that keep the codebase modular, readable, and easy to evolve.

## 1. Big Picture

The project is split by business responsibility:

- `src/core`: global shell lifecycle and command context.
- `src/builtins`: internal commands (`env`, `setenv`, `unsetenv`, `cd`).
- `src/execution`: execution orchestration (dispatch, external, pipeline, redirections).
- `src/environment`: environment access and binary resolution through PATH.
- `src/parsing`: parsing token extraction (for example redirections).
- `src/utils`: low-level utility functions (string, io, validation).
- `src/memory`: destruction and cleanup of dynamic structures.

The `include` directory follows the same logic with APIs separated by domain.

## 2. Detailed Layout

### 2.1 Core

- `src/core/main.c`: REPL loop, input reading, executor call.
- `src/core/init/init_env.c`: build the environment linked list.
- `src/core/init/init_main.c`: initialize the global `main_t` state.
- `src/core/context/command_context.c`: parse a command into `command_ctx_t`.

### 2.2 Builtins

- `src/builtins/env/my_env.c`: display the environment.
- `src/builtins/env/my_setenv.c`: add/update an environment variable.
- `src/builtins/env/my_unsetenv.c`: remove an environment variable.
- `src/builtins/fs/my_chdir.c`: `cd` implementation.

### 2.3 Execution

- `src/execution/dispatch/execute_command.c`: split by `;` and global orchestration.
- `src/execution/dispatch/execute_single_command.c`: non-pipeline path, builtin/external.
- `src/execution/dispatch/execute_builtin.c`: builtin registry and dispatch.
- `src/execution/external/exec_any.c`: command resolution and external launch.
- `src/execution/external/run_fork.c`: fork + wait + status.
- `src/execution/external/exec_error_case.c`: `execve` error handling and signals.
- `src/execution/pipeline/*`: parse/spawn/wait/finalize for pipelines.
- `src/execution/redirection/apply_redirection.c`: apply redirections.

### 2.4 Environment

- `src/environment/query/get_home.c`: read HOME.
- `src/environment/query/get_path.c`: read PATH.
- `src/environment/path/check_bin.c`: executable resolution in PATH.

### 2.5 Parsing

- `src/parsing/redirection/get_redirection.c`: redirection token detection.

### 2.6 Utils

- `src/utils/strings/*`: custom string helpers.
- `src/utils/io/my_putstr.c`: stdout/stderr output.
- `src/utils/validation/*`: argument validation.

### 2.7 Memory

- `src/memory/free/free_function.c`: cleanup of dynamic structures.

## 3. Core Types

The central types are declared in `include/core/types.h`:

- `env_t`: linked-list `key/value` node for the environment.
- `main_t`: global shell state (long-lived).
- `command_ctx_t`: ephemeral command state.
- `pipeline_segment_t`: representation of one pipeline segment.
- `pipeline_state_t`: execution context for a pipeline.

## 4. Modular Boundaries

Key modularity rules:

- `dispatch` modules do not contain business logic for redirections.
- `external` modules do not parse commands; they consume an already valid context.
- Builtins are called through a registry (`builtin_command_t`) and a shared signature.
- Redirection parsing is isolated from fork/exec code.
- The pipeline is handled as an independent unit with its own state.

## 5. Execution Flow

Nominal path:

1. `main` reads a line.
2. `execute_command` splits the line on `;`.
3. Each segment goes either to `execute_pipeline` or `execute_single_command`.
4. `execute_single_command` parses `command_ctx_t`.
5. If the builtin is known: execute the builtin handler.
6. Otherwise: `exec_any` -> `run_fork` -> `child_exec`.
7. Status is returned to the REPL.

## 6. Header APIs by Domain

Public entry points are separated:

- `include/core/core.h`
- `include/builtins/builtins.h`
- `include/execution/execution.h`
- `include/environment/environment.h`
- `include/parsing/parsing.h`
- `include/utils/utils.h`
- `include/memory/memory.h`

The `include/c_zsh.h` file acts as an aggregator facade for compatibility.

## 7. Recommended Evolution

To remain modular over time:

- Add each new feature in an existing or new subdomain, never in a catch-all file.
- Keep functions `static` when they are not exported.
- Keep functions small and separate parsing, validation, and execution.
- Document any new structure in `docs/OWNERSHIP.md`.
- Add at least one unit test for every new critical code path.

## 8. Pre-merge Checklist

- The module has a clear domain (`core`, `execution`, `builtins`, etc.).
- The header exports only what is necessary.
- The code does not depend on a global field when a local context exists.
- Allocations have an explicit destructor.
- `make re` and `make unit_tests` pass.
