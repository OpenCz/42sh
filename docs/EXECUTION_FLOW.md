# Execution Flow

This document describes the minishell runtime step by step.

## 1. Main Loop

File: `src/core/main.c`

- initializes `main_t` via `init_main`;
- reads the user line;
- normalizes the trailing newline;
- calls `execute_command`;
- keeps the last exit status.

## 2. Line-Level Dispatch

File: `src/execution/dispatch/execute_command.c`

- splits the line by `;`;
- for each subcommand:
  - if `|` is present: sends it to `execute_pipeline`;
  - otherwise: sends it to `execute_single_command`.

## 3. Single Command

File: `src/execution/dispatch/execute_single_command.c`

- parses into `command_ctx_t`;
- tries a builtin through the registry;
- otherwise executes externally (`exec_any`);
- cleans up the context before returning.

## 4. Builtin Dispatch

File: `src/execution/dispatch/execute_builtin.c`

- `builtin_command_t` table (`name` + handler);
- command-name comparison;
- execution of the matching handler;
- `-1` if the command is not a builtin.

## 5. External Execution

Files:

- `src/execution/external/exec_any.c`
- `src/execution/external/run_fork.c`
- `src/execution/external/exec_error_case.c`

Steps:

1. resolve the binary (absolute/relative command or PATH)
2. build a temporary envp
3. `fork`
4. child: redirection then `execve`
5. parent: `waitpid` and status normalization

## 6. Redirections

File: `src/execution/redirection/apply_redirection.c`

- detects the token index (`>`, `>>`, `<`)
- opens the target fd
- applies `dup2` on stdin/stdout
- cuts `argv` at the redirection token

## 7. Pipeline

Files:

- `src/execution/pipeline/pipeline_parse.c`
- `src/execution/pipeline/pipeline_spawn.c`
- `src/execution/pipeline/pipeline_wait.c`
- `src/execution/pipeline/pipeline_execute.c`

Steps:

1. syntax validation of pipes
2. parsing into `pipeline_segment_t[]`
3. `pids` allocation
4. creation of intermediate pipes
5. spawn each segment
6. wait and return the last segment status
7. global pipeline cleanup

## 8. Env/Fs Builtins

- `builtin_env`: prints the `stock_env` list
- `builtin_setenv`: adds/updates a variable
- `builtin_unsetenv`: removes a variable
- `builtin_cd`: changes directory and handles `old_path`

## 9. Error Handling

- parsing errors: immediate non-zero status
- fork/exec errors: shell-compliant status
- signal errors (segfault/fpe): normalization via `get_seg`

## 10. Runtime Invariants

- a `command_ctx_t` is always cleaned up at the end of a single command
- a `pipeline_state_t` is always freed on success or error
- no external command should depend on temporary global fields
