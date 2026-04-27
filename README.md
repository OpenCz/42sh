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
│   ├── c_zsh.h                         # aggregator facade
│   ├── builtins/builtins.h
│   ├── config/czshrc.h
│   ├── core/
│   │   ├── core.h
│   │   └── types.h                     # structs: env_t, main_t, command_ctx_t, pipeline_*
│   ├── environment/environment.h
│   ├── execution/execution.h
│   ├── memory/memory.h
│   ├── parsing/parsing.h
│   └── utils/
│       ├── defines.h
│       └── utils.h
├── src/
│   ├── core/
│   │   ├── main.c                      # REPL loop (getline)
│   │   ├── context/command_context.c   # command parsing -> command_ctx_t
│   │   └── init/
│   │       ├── init_env.c              # build linked env list
│   │       └── init_main.c             # initialize main_t
│   ├── builtins/
│   │   ├── env/                        # env, setenv, unsetenv
│   │   ├── fs/                         # cd
│   │   ├── jobs/                       # fg, bg, jobs (stubs)
│   │   └── repeat/                     # repeat
│   ├── environment/
│   │   ├── path/check_bin.c            # executable resolution in PATH
│   │   └── query/                      # get_home, get_path
│   ├── execution/
│   │   ├── dispatch/                   # orchestration (builtin, single, operator)
│   │   ├── external/                   # fork/exec, error handling
│   │   ├── pipeline/                   # parse/spawn/wait pipeline
│   │   └── redirection/               # apply_redirection
│   ├── parsing/
│   │   ├── quotes_management/          # double-quote handling
│   │   └── redirection/               # redirection token detection
│   ├── memory/free/                    # structure cleanup
│   └── utils/
│       ├── display/                    # prompt, git branch, current directory
│       ├── io/                         # putstr, openator, file size
│       ├── strings/                    # strcmp, strdup, strconcat, word arrays...
│       └── validation/                 # ischar_num, str_is_alphanum
├── tests/                              # unit tests
└── docs/
    ├── ARCHITECTURE.md
    ├── EXECUTION_FLOW.md
    └── G-PSU-200_42sh.pdf
```

---

## Progress Status

### Done

| Feature | Details |
|---|---|
| **REPL loop** | Read via `getline`, prompt display, EOF handling |
| **Styled prompt** | Displays current directory + git branch (ANSI colors) |
| **`;` separator** | Multiple commands on one line |
| **`&&` / `\|\|` operators** | Conditional execution |
| **Pipes `\|`** | Multi-segment pipeline with fork/exec |
| **Redirections `>` `>>` `<` `<<`** | Stdout, append, stdin, heredoc |
| **Double quotes `"`** | Escape sequence interpretation (`\n`, `\t`, etc.) |
| **Single quotes `'`** | Literal handling, no expansion |
| **External execution** | `fork` + `execve`, PATH resolution |
| **`env`** | Prints environment variables |
| **`setenv`** | Defines an environment variable |
| **`unsetenv`** | Removes an environment variable |
| **`cd`** | Changes directory |
| **`repeat`** | `repeat N cmd` — runs `cmd` N times |
| **External error handling** | Error messages and return codes aligned with tcsh |
| **Unit tests** | Coverage for main modules (redirections, builtins, pipeline, parsing...) |

---

### In progress / Stubs

These features are **registered in the builtin registry** but their logic is empty (they return `0` without doing anything).

| Feature | File | Status |
|---|---|---|
| **`jobs`** | `src/builtins/jobs/my_jobs.c` | Empty stub |
| **`fg`** | `src/builtins/jobs/my_foreground.c` | Empty stub |
| **`bg`** | `src/builtins/jobs/my_background.c` | Empty stub |

---

### Not yet implemented

#### Mandatory

| Feature | Description |
|---|---|
| **Globbing `*` `?` `[` `]`** | File expansion, error message if no match |
| **Job control `&`** | Background execution, `[job_id] pid` display |
| **Full job control** | `SIGCHLD`, `SIGTSTP` (Ctrl+Z), job list, final status |
| **Backticks `` `cmd` ``** | Command substitution in the current line |
| **Parentheses `(cmd1; cmd2)`** | Execution in a subshell |
| **Local variables `set` / `unset`** | Variables visible only in the current shell |
| **`$var` expansion** | Replacement of local and environment variables |
| **Special variables `$cwd` `$term`** | Automatic updates, hooks |
| **`$precmd` hook** | Runs before each prompt display |
| **`$cwdcmd` hook** | Runs on each directory change |
| **`$ignoreof`** | Ctrl+D does not exit when defined |
| **`$$` `$?var` `$#var`** | PID, variable existence, array size |
| **History `!` `!!` `!n`** | History expansion before any other processing |
| **Builtin `history`** | Prints numbered history |
| **Aliases `alias` / `unalias`** | Definition, expansion, removal, listing |
| **Line editing (ncurses)** | Current state: raw `getline`. To do: arrows, Ctrl+A/E/W/U, Tab, Home/End |
| **Auto-completion** | Tab -> files, PATH commands, `$` variables |
| **Multiline editing** | Continuation with `\` or open parentheses |
| **Scripting** | `./script.csh` or `42sh script.csh`, non-interactive stdin reading |
| **Builtin `echo`** | Currently delegated to an external command |
| **Builtin `exit [code]`** | Currently handled by `strcmp` in `main`, no configurable exit code |
| **Redirections `2>` `>&`** | Stderr and combined stdout+stderr |

#### Builtins missing from the registry

| Builtin | Description |
|---|---|
| `echo` | Print arguments (internal builtin) |
| `exit [code]` | Exit with a return code |
| `set` | Local variables / list all variables |
| `unset` | Remove a local variable |
| `alias` | Define / list aliases |
| `unalias` | Remove an alias |
| `history` | Display the history |

#### Signals

| Signal | Status |
|---|---|
| `SIGINT` (Ctrl+C) | Partially handled (interrupts the child process) |
| `SIGQUIT` (Ctrl+\\) | Not explicitly handled |
| `SIGTSTP` (Ctrl+Z) | Not implemented (job control) |
| `SIGCHLD` | Not implemented (needed for job control) |
| `SIGHUP` | Not implemented |

---

### Bonus (not started)

| Feature |
|---|
| `foreach`, `while`, `if/else/endif` |
| Advanced completion (options, man pages) |
| Customizable `$prompt` |
| `source` / `.` |
| Persistent history `~/.history` |
| `pushd` / `popd` / `dirs` |
| `~user` expansion |
| `$path` as a tcsh-style array |

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
