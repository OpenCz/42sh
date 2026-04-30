# Execution Flow

This document walks through the 42sh runtime step by step, from shell startup
to the return of a single command's exit status.

---

## 1. Shell Startup

File: `src/core/init/`

1. `init_main(env)` allocates the global `main_t` and calls:
   - `init_env(env)` — walk `environ`, build a singly-linked `env_t` list.
   - `get_path()` — split `PATH` into a `char **` array.
   - `get_home()` — store `HOME` in `main_t.home`.
   - `init_history()` — allocate `history_t`, load `~/.c_zsh_history`.
2. `setup_shell_signals()` — the shell process ignores `SIGINT`, `SIGTSTP`,
   `SIGTTOU`, `SIGTTIN`, `SIGQUIT`; calls `setpgid` and `tcsetpgrp` to
   become the foreground process-group leader.
3. `update_rc()` — load `.c_zshrc` or apply `set_default_rc()`.

---

## 2. Main REPL Loop

File: `src/core/main.c`

```
while (buffer != "exit") {
    write_print(stock)           // display styled prompt
    cmd = get_command(...)       // read one line
    if (cmd == CONTINUE) continue;
    execute_command(buffer)
}
```

The `loop_state_t` struct tracks the current buffer, the last exit status,
and a flag to avoid double-drawing the prompt after a Ctrl+C clear.

---

## 3. Interactive Input Loop

File: `src/core/context/get_command.c`

When stdin is a TTY, `create_command()` switches the terminal to raw mode
(`ICANON=0`, `ECHO=0`) and runs a character-by-character loop:

```
init_termios()       // disable ICANON + ECHO
for (cursor = 0; status == 0;) {
    print_command()  // redraw current buffer
    read(STDIN, &ch, 1)
    check_char()     // dispatch on ch
}
restore_termios()
```

Key dispatch table:

| Input | Action |
|---|---|
| `0x0A` Enter | `status = 1` → exit loop, line is ready |
| `0x03` Ctrl+C | clear buffer, redisplay prompt, `status = CONTINUE` |
| `0x04` Ctrl+D | exit shell (empty buffer) or submit line (non-empty) |
| `0x0C` Ctrl+L | clear screen, redraw prompt |
| `0x01` Ctrl+A | move cursor to start of line |
| `0x05` Ctrl+E | move cursor to end of line |
| `0x7F` Backspace | delete character before cursor |
| `0x1B` Escape | enter `arrow_handling()` for escape sequences |
| Up arrow `\x1b[A` | load previous history entry, save current input |
| Down arrow `\x1b[B` | load next history entry or restore saved input |
| Left/Right `\x1b[C/D` | move cursor within the line |
| Other | insert character at cursor position |

When stdin is not a TTY (script or pipe), `getline()` is used instead.

---

## 4. Line-Level Dispatch

File: `src/execution/dispatch/execute_command.c`

```c
char **commands = my_str_to_word_array_quote(line, ";");
for (int i = 0; commands[i]; i++)
    last = execute_compound_command(stock, commands[i]);
```

Each semicolon-separated segment is dispatched based on what operators it contains:

| Contains | Dispatched to |
|---|---|
| `\|` pipe | `execute_pipeline()` |
| `&&` or `\|\|` | `execute_operator()` |
| neither | `execute_single_command()` |

---

## 5. Logical Operator Loop

File: `src/execution/dispatch/execute_operation.c`

The input is split into a `commands[]` array and a parallel `operators[]`
array (`"&&"` or `"||"`).

```c
status = execute_single_command(commands[0]);
for (int i = 1; commands[i]; i++) {
    if (operators[i-1] == "&&" && status == 0)
        status = execute_single_command(commands[i]);
    if (operators[i-1] == "||" && status != 0)
        status = execute_single_command(commands[i]);
    // otherwise: skip
}
```

Short-circuit evaluation: a failing `&&` or passing `||` skips all remaining
commands up to the next separator.

---

## 6. Single Command Path

File: `src/execution/dispatch/execute_single_command.c`

1. `parse_command_context()` → builds `command_ctx_t` (command name, argv, redirection token).
2. `replace_env_vars(argv)` — iterate every `argv` token, replace `$VAR` / `${VAR}` by looking up `stock_env`.
3. `execute_builtin()` — linear search through the `builtin_command_t` registry.
   - Match found → call the handler, return its exit code.
   - No match → return `-1`, fall through to external execution.
4. `exec_any()` → external execution path.
5. `clear_command_ctx()` — free the ephemeral context.

---

## 7. Builtin Registry

File: `src/execution/dispatch/execute_builtin.c`

```c
for (size_t i = 0; command_shell[i].name; i++) {
    if (strcmp(cmd, command_shell[i].name) == 0)
        return command_shell[i].func(main_stock, ctx);
}
return -1;
```

Registered builtins:

| Name | Handler | Status |
|---|---|---|
| `env` | `builtin_env` | Implemented |
| `setenv` | `builtin_setenv` | Implemented |
| `unsetenv` | `builtin_unsetenv` | Implemented |
| `printenv` | `builtin_printenv` | Implemented |
| `cd` | `builtin_cd` | Implemented |
| `which` | `builtin_which` | Implemented |
| `where` | `builtin_where` | Implemented |
| `repeat` | `builtin_repeat` | Implemented |
| `foreach` | `builtin_foreach` | Implemented |
| `history` | `builtin_history` | Implemented |
| `source` | `source` | Implemented |
| `jobs` | `builtin_jobs` | Stub |
| `fg` | `builtin_foreground` | Stub |
| `bg` | `builtin_background` | Stub |

---

## 8. External Execution

Files: `src/execution/external/exec_any.c`, `run_fork.c`, `exec_error_case.c`

1. `check_bin()` — resolve the binary: absolute/relative path or search every PATH entry.
2. Build `envp` from `stock_env` linked list.
3. `run_fork()`:
   - **child**: restore default signals (`SIGTSTP`, `SIGTTOU`, `SIGTTIN`), call
     `setpgid(0, 0)`, give terminal with `tcsetpgrp`, call
     `apply_redirection()`, then `execve(bin, argv, envp)`.
   - **parent**: `setpgid(pid, pid)`, `tcsetpgrp` to child,
     `waitpid(pid, &status, WUNTRACED)`.
4. Status normalization (`get_seg`):

| Condition | Exit code |
|---|---|
| `WIFEXITED` | `WEXITSTATUS(status)` |
| `WIFSTOPPED` | print `"Suspended"`, return `1` |
| `WIFSIGNALED(SIGINT)` | `130` |
| `WIFSIGNALED(SIGSEGV)` | print `"Segmentation fault (core dumped)"`, return `139` |
| `WIFSIGNALED(SIGFPE)` | print `"Floating exception (core dumped)"`, return `136` |

5. Parent restores the terminal with `tcsetpgrp(STDIN, shell_pgid)`.

---

## 9. Pipeline

Files: `src/execution/pipeline/`

1. `pipeline_syntax_check()` — reject leading/trailing/consecutive `|`.
2. `pipeline_parse()` — split on `|` into `pipeline_segment_t[]`.
3. Allocate `pipe()` pairs and `pids[]`.
4. **Segment spawn loop** (`pipeline_spawn.c`):
   ```c
   for (int i = 0; i < count; i++) {
       pipe(next_fds);
       pid = fork();
       // child: dup2 prev_read→STDIN, dup2 next_write→STDOUT, close unused FDs, execve
       // parent: close prev_read, close next_write, prev_read = next_fds[0]
   }
   ```
5. **Wait loop** (`pipeline_wait.c`):
   ```c
   for (int i = 0; i < count; i++)
       waitpid(pids[i], &status, WUNTRACED);
   // return last segment's normalized status
   ```
6. Free `pipeline_state_t`.

---

## 10. Redirections

File: `src/execution/redirection/apply_redirection.c`

Called inside the child process before `execve`:

1. Scan `argv` for a redirection token (`>>`, `<<`, `>`, `<`).
2. Open the target file with the appropriate flags:
   - `>` → `O_WRONLY | O_CREAT | O_TRUNC`
   - `>>` → `O_WRONLY | O_CREAT | O_APPEND`
   - `<` → `O_RDONLY`
   - `<<` → heredoc: write lines until delimiter to a temp FD
3. `dup2(fd, STDOUT_FILENO)` or `dup2(fd, STDIN_FILENO)`.
4. Truncate `argv` at the token position so `execve` does not see the redirection.

---

## 11. foreach Builtin

File: `src/builtins/scripts/foreach.c`

```
foreach var (item1 item2 … itemN)
    cmd1
    cmd2
end
```

Execution:

1. Read all body lines until `"end"` into `cmd[][]`.
2. **Outer loop** — for each item in the argument list:
   ```c
   for (int i = 1; args[i]; i++) {
       setenv(loop_var, args[i]);
       // inner loop:
       for (int j = 0; cmd[j]; j++) {
           parse_command_context(cmd[j]);
           exec_any();
       }
       restore_or_unset(loop_var);
   }
   ```
3. `$var` substitution inside the body resolves to the current item via
   `replace_env_vars` on each inner iteration.

---

## 12. repeat Builtin

File: `src/builtins/repeat/repeat.c`

```c
for (int i = 0; i < N; i++)
    status = exec_any(main_stock, &ctx);
return status;
```

Parses `N` as an integer, validates that it is non-negative, then calls
`exec_any` with the same context on every iteration.

---

## 13. Error Handling

- Parsing errors: immediate non-zero status returned to the REPL.
- `execve` failures: `exec_error_case` prints a tcsh-compliant message and exits the child.
- Signal-induced deaths: `get_seg` maps signal numbers to tcsh-standard exit codes.
- Stopped children (`WIFSTOPPED`): print `"Suspended"`, return `1` to the REPL (full job control pending).

---

## 14. Runtime Invariants

- A `command_ctx_t` is always cleaned up at the end of a single command.
- A `pipeline_state_t` is always freed on both success and error paths.
- No external command depends on temporary global fields in `main_t`.
- The terminal (`tcsetpgrp`) is always restored to the shell after a child exits or stops.
- The history file is flushed on each new entry.
