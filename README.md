# 42sh

Unix shell compatible with **TCSH**, written in C as part of the Epitech PSU project.

## Authors

- `@Celz-Pch`
- `@Lukas-sgx`
- `@Jessymgadd`
- `@sacha-lma`
- `@ErwanTheKing`

---

## Build & Run

```bash
make          # build the ./42sh binary
make re       # rebuild from scratch
make clean    # remove .o files
make fclean   # remove .o files and the binary
./42sh        # start the interactive shell
./42sh script.csh  # run a script (not implemented yet)
```

---

## Project Architecture

```
42sh/
├── Makefile
├── include/
│   ├── c_zsh.h                                  # aggregator facade
│   ├── builtins/builtins.h
│   ├── config/
│   │   ├── czshrc.h                             # RC configuration structs
│   │   └── color.h                              # ANSI color definitions
│   ├── core/
│   │   ├── core.h
│   │   └── types.h                              # env_t, main_t, command_ctx_t,
│   │                                            # pipeline_*, history_t, czshrc_t
│   ├── environment/environment.h
│   ├── execution/execution.h
│   ├── memory/memory.h
│   ├── parsing/parsing.h
│   └── utils/
│       ├── defines.h
│       └── utils.h
├── src/
│   ├── core/
│   │   ├── main.c                               # REPL loop + loop state
│   │   ├── context/
│   │   │   ├── get_command.c                    # interactive input loop (raw termios)
│   │   │   ├── command_context.c                # parse line → command_ctx_t
│   │   │   ├── key_binding.c                    # Ctrl+C / Ctrl+D / Ctrl+L handlers
│   │   │   ├── arrow_handling.c                 # arrow key navigation
│   │   │   ├── manage_history.c                 # history push / load / navigate
│   │   │   ├── termios.c                        # terminal raw mode helpers
│   │   │   ├── signal.c                         # shell-level signal setup
│   │   │   ├── display.c                        # in-line display helpers
│   │   │   └── tab.c                            # tab completion (stub)
│   │   └── init/
│   │       ├── init_env.c                       # build environment linked list
│   │       └── init_main.c                      # initialize global main_t
│   ├── builtins/
│   │   ├── env/                                 # env, setenv, unsetenv, printenv
│   │   ├── fs/                                  # cd, which, where
│   │   ├── jobs/                                # fg, bg, jobs (stubs)
│   │   ├── repeat/                              # repeat N cmd
│   │   ├── scripts/                             # foreach loop
│   │   ├── history/                             # history builtin
│   │   └── config/                              # source / .
│   ├── config/
│   │   ├── czshrc.c                             # RC file loading / parsing
│   │   ├── manage_prompt.c                      # prompt configuration
│   │   └── set_default_rc.c                     # default settings
│   ├── environment/
│   │   ├── path/check_bin.c                     # executable resolution in PATH
│   │   └── query/                               # get_home, get_path, get_user
│   ├── execution/
│   │   ├── dispatch/                            # orchestration (builtin, single, operator)
│   │   ├── external/                            # fork/exec, error handling, signals
│   │   ├── pipeline/                            # parse/spawn/wait pipeline
│   │   └── redirection/                         # apply_redirection
│   ├── parsing/
│   │   ├── quotes_management/                   # double-quote handling + escape sequences
│   │   ├── redirection/                         # redirection token detection
│   │   └── env_var_management/                  # $VAR substitution
│   ├── memory/free/                             # structure cleanup
│   └── utils/
│       ├── display/                             # prompt, git branch, current dir, time
│       ├── io/                                  # putstr, openator, file size
│       ├── strings/                             # strcmp, strdup, strconcat, word arrays…
│       └── validation/                          # ischar_num, str_is_alphanum
├── tests/                                       # unit tests (20+ files)
└── docs/
    ├── ARCHITECTURE.md
    ├── EXECUTION_FLOW.md
    └── ARCHITECTURE_DIAGRAM.mmd                 # Mermaid architecture + loop diagram
```

---

## Progress Status

### Done

| Feature | Details |
|---|---|
| **REPL loop** | Interactive raw-termios input + non-interactive `getline`, EOF handling |
| **Styled prompt** | Current directory + git branch, ANSI colors, configurable via `.c_zshrc` |
| **Line editing** | Arrow keys (↑↓←→), Ctrl+A/E (start/end), Ctrl+L (clear screen), Backspace, cursor movement |
| **History navigation** | Up/Down arrows cycle through history; input saved/restored when navigating |
| **Persistent history** | Saved to `~/.c_zsh_history` across sessions |
| **`;` separator** | Multiple commands on one line |
| **`&&` / `\|\|` operators** | Short-circuit conditional execution |
| **Pipes `\|`** | Multi-segment pipeline with proper fork/exec and FD management |
| **Redirections `>` `>>` `<` `<<`** | Stdout overwrite, append, stdin, heredoc |
| **Double quotes `"`** | Escape sequence interpretation (`\n`, `\t`, `\r`, `\\`, `\"`, etc.) |
| **Single quotes `'`** | Literal handling, no expansion |
| **`$VAR` substitution** | Environment variable replacement in command arguments |
| **External execution** | `fork` + `execve`, PATH resolution |
| **`env`** | Prints all environment variables (`KEY=VALUE`) |
| **`setenv`** | Defines or updates an environment variable |
| **`unsetenv`** | Removes an environment variable |
| **`printenv`** | Prints a specific environment variable |
| **`cd`** | Changes directory; supports `~`, `-` (previous dir), updates `PWD`/`OLDPWD` |
| **`which`** | Locates first occurrence of a command in PATH |
| **`where`** | Lists all occurrences of a command in PATH |
| **`repeat`** | `repeat N cmd` — runs `cmd` exactly N times |
| **`foreach`** | `foreach var (items) … end` — loop over a list, sets loop variable |
| **`history`** | Displays numbered command history with timestamps |
| **`source`** | `source file` / `. file` — executes commands from a file |
| **External error handling** | Error messages and return codes aligned with tcsh |
| **SIGTSTP (Ctrl+Z)** | Foreground child processes can be suspended; shell detects via `WUNTRACED`, prints "Suspended" |
| **Unit tests** | Coverage for main modules (redirections, builtins, pipeline, parsing…) |

---

### In progress / Stubs

These features are **registered in the builtin registry** but their logic is empty (they return `0` without doing anything).

| Feature | File | Status |
|---|---|---|
| **`jobs`** | `src/builtins/jobs/my_jobs.c` | Empty stub |
| **`fg`** | `src/builtins/jobs/my_foreground.c` | Empty stub |
| **`bg`** | `src/builtins/jobs/my_background.c` | Empty stub |
| **Tab completion** | `src/core/context/tab.c` | Stub — no file/command completion yet |

---

### Not yet implemented

#### Mandatory

| Feature | Description |
|---|---|
| **Globbing `*` `?` `[` `]`** | File expansion, error message if no match |
| **Background execution `&`** | Launch process in background, display `[job_id] pid` |
| **Full job control** | `SIGCHLD` handler, job list data structure, working `fg`/`bg`/`jobs` |
| **Backticks `` `cmd` ``** | Command substitution inline |
| **Parentheses `(cmd1; cmd2)`** | Execution in a subshell |
| **Local variables `set` / `unset`** | Variables visible only in the current shell |
| **Special variables `$cwd` `$term`** | Automatic updates on directory change |
| **`$precmd` hook** | Runs before each prompt display |
| **`$cwdcmd` hook** | Runs on each directory change |
| **`$ignoreof`** | Ctrl+D does not exit when defined |
| **`$$` `$?var` `$#var`** | PID, variable existence, array size |
| **History expansion `!` `!!` `!n`** | History substitution before any other processing |
| **Aliases `alias` / `unalias`** | Definition, expansion, removal, listing |
| **Ctrl+W / Ctrl+U** | Delete word / delete to start of line |
| **Tab auto-completion** | Files, PATH commands, `$` variables |
| **Multiline editing** | Continuation with `\` or open parentheses |
| **Scripting** | `./script.csh` or `42sh script.csh`, non-interactive stdin reading |
| **Builtin `echo`** | Currently delegated to external command |
| **Builtin `exit [code]`** | Currently handled by `strcmp("exit")` in main; no configurable exit code |
| **Redirections `2>` `>&`** | Stderr and combined stdout+stderr |

#### Builtins missing from the registry

| Builtin | Description |
|---|---|
| `echo` | Print arguments (internal builtin) |
| `exit [code]` | Exit with a configurable return code |
| `set` | Local variables / list all variables |
| `unset` | Remove a local variable |
| `alias` | Define / list aliases |
| `unalias` | Remove an alias |

#### Signals

| Signal | Status |
|---|---|
| `SIGINT` (Ctrl+C) | Shell ignores; interrupts and terminates active child process (exit 130) |
| `SIGQUIT` (Ctrl+\\) | Shell ignores |
| `SIGTSTP` (Ctrl+Z) | Partial — child process can be suspended; shell detects stop via `WUNTRACED`; full job control (resume, list) pending |
| `SIGCHLD` | Not implemented (needed for complete job control) |
| `SIGHUP` | Not implemented |
| `SIGTTOU` / `SIGTTIN` | Shell ignores (proper terminal management for process groups) |

---

### Bonus (not started)

| Feature |
|---|
| `while` / `if`/`else`/`endif` control flow |
| Advanced completion (options, man pages) |
| `pushd` / `popd` / `dirs` |
| `~user` home expansion |
| `$path` as a tcsh-style array variable |

---

## Expansion Order (tcsh reference)

1. History (`!`, `!!`, `!n`)
2. Aliases
3. Parsing / tokenization
4. Variables (`$var`, `$$`, etc.)
5. Backticks (`` `cmd` ``)
6. Globbing (`*`, `?`, `[`, `]`)

---

## Watchpoints

- No memory leaks tolerated — validate with Valgrind.
- Compile without warnings with `-Wall -Wextra`.
- Never break a working feature when adding a new one.
- Behavior must match `tcsh` exactly (return codes, error messages).
- `make re` must rebuild from scratch.
- Do not ship `.o` files, binaries, or temporary files.
