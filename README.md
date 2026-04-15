# 42sh

Shell Unix complet compatible **TCSH**, développé en C dans le cadre du projet PSU Epitech.

## Auteurs

- `@Celz-Pch`
- `@Lukas-sgx`
- `@Jessymgadd`
- `@sacha-lma`
- `@ErwanTheKing`

---

## Compilation & lancement

```bash
make          # compile le binaire ./42sh
make re       # recompile depuis zéro
make clean    # supprime les .o
make fclean   # supprime les .o et le binaire
./42sh        # lance le shell interactif
./42sh script.csh  # exécute un script (non encore implémenté)
```

---

## Architecture du projet

```
42sh/
├── Makefile
├── include/
│   ├── c_zsh.h                         # façade agrégratrice
│   ├── builtins/builtins.h
│   ├── config/czshrc.h
│   ├── core/
│   │   ├── core.h
│   │   └── types.h                     # structs : env_t, main_t, command_ctx_t, pipeline_*
│   ├── environment/environment.h
│   ├── execution/execution.h
│   ├── memory/memory.h
│   ├── parsing/parsing.h
│   └── utils/
│       ├── defines.h
│       └── utils.h
├── src/
│   ├── core/
│   │   ├── main.c                      # boucle REPL (getline)
│   │   ├── context/command_context.c   # parsing commande → command_ctx_t
│   │   └── init/
│   │       ├── init_env.c              # construction liste chaînée env
│   │       └── init_main.c             # initialisation main_t
│   ├── builtins/
│   │   ├── env/                        # env, setenv, unsetenv
│   │   ├── fs/                         # cd
│   │   ├── jobs/                       # fg, bg, jobs (stubs)
│   │   └── repeat/                     # repeat
│   ├── environment/
│   │   ├── path/check_bin.c            # résolution exécutable dans PATH
│   │   └── query/                      # get_home, get_path
│   ├── execution/
│   │   ├── dispatch/                   # orchestration (builtin, single, operator)
│   │   ├── external/                   # fork/exec, gestion erreurs
│   │   ├── pipeline/                   # parse/spawn/wait pipeline
│   │   └── redirection/               # apply_redirection
│   ├── parsing/
│   │   ├── quotes_management/          # gestion guillemets doubles
│   │   └── redirection/               # détection token redirection
│   ├── memory/free/                    # libération des structures
│   └── utils/
│       ├── display/                    # prompt, git branch, dossier courant
│       ├── io/                         # putstr, openator, file size
│       ├── strings/                    # strcmp, strdup, strconcat, word arrays...
│       └── validation/                 # ischar_num, str_is_alphanum
├── tests/                              # tests unitaires
└── docs/
    ├── ARCHITECTURE.md
    ├── EXECUTION_FLOW.md
    └── G-PSU-200_42sh.pdf
```

---

## Etat d'avancement

### Fait

| Feature | Détail |
|---|---|
| **Boucle REPL** | Lecture via `getline`, affichage du prompt, gestion EOF |
| **Prompt stylisé** | Affiche le dossier courant + branche git (ANSI couleurs) |
| **Séparateur `;`** | Plusieurs commandes sur une ligne |
| **Opérateurs `&&` / `\|\|`** | Exécution conditionnelle |
| **Pipes `\|`** | Pipeline multi-segments avec fork/exec |
| **Redirections `>` `>>` `<` `<<`** | Stdout, append, stdin, heredoc |
| **Guillemets doubles `"`** | Interprétation des séquences d'échappement (`\n`, `\t`, etc.) |
| **Guillemets simples `'`** | Traitement littéral, aucune expansion |
| **Exécution externe** | `fork` + `execve`, résolution dans `PATH` |
| **`env`** | Affiche les variables d'environnement |
| **`setenv`** | Définit une variable d'environnement |
| **`unsetenv`** | Supprime une variable d'environnement |
| **`cd`** | Change de répertoire |
| **`repeat`** | `repeat N cmd` — exécute `cmd` N fois |
| **Gestion erreurs externes** | Messages d'erreur et codes de retour conformes à tcsh |
| **Tests unitaires** | Couverture des modules principaux (redirections, builtins, pipeline, parsing…) |

---

### En cours / Stubs

Ces features sont **enregistrées dans le registre des builtins** mais leur logique est vide (retournent `0` sans rien faire).

| Feature | Fichier | Etat |
|---|---|---|
| **`jobs`** | `src/builtins/jobs/my_jobs.c` | Stub vide |
| **`fg`** | `src/builtins/jobs/my_foreground.c` | Stub vide |
| **`bg`** | `src/builtins/jobs/my_background.c` | Stub vide |

---

### Pas encore implémenté

#### Mandatory

| Feature | Description |
|---|---|
| **Globbing `*` `?` `[` `]`** | Expansion de fichiers, message d'erreur si aucun match |
| **Job control `&`** | Lancement en arrière-plan, affichage `[job_id] pid` |
| **Job control complet** | Gestion `SIGCHLD`, `SIGTSTP` (Ctrl+Z), liste des jobs, statut à la fin |
| **Backticks `` `cmd` ``** | Substitution de commande dans la ligne courante |
| **Parenthèses `(cmd1; cmd2)`** | Exécution dans un sous-shell |
| **Variables locales `set` / `unset`** | Variables visibles uniquement dans le shell courant |
| **Expansion `$var`** | Remplacement des variables locales et d'environnement |
| **Variables spéciales `$cwd` `$term`** | Mise à jour automatique, hooks |
| **Hook `$precmd`** | Exécuté avant chaque affichage du prompt |
| **Hook `$cwdcmd`** | Exécuté à chaque changement de répertoire |
| **`$ignoreof`** | Ctrl+D ne quitte pas si définie |
| **`$$` `$?var` `$#var`** | PID, existence variable, taille array |
| **Historique `!` `!!` `!n`** | Expansion de l'historique avant tout autre traitement |
| **Builtin `history`** | Affichage de l'historique numéroté |
| **Aliases `alias` / `unalias`** | Définition, expansion, suppression, listage |
| **Line edition (ncurses)** | Actuellement : `getline` brut. A faire : flèches, Ctrl+A/E/W/U, Tab, Home/End |
| **Auto-complétion** | Tab → fichiers, commandes PATH, variables `$` |
| **Édition multiline** | Continuation avec `\` ou parenthèses ouvertes |
| **Scripting** | `./script.csh` ou `42sh script.csh`, lecture stdin non-interactif |
| **Builtin `echo`** | Actuellement délégué à l'externe |
| **Builtin `exit [code]`** | Actuellement géré par `strcmp` dans `main`, pas de code de retour paramétrable |
| **Redirections `2>` `>&`** | Stderr et stdout+stderr combinés |

#### Builtins manquants dans le registre

| Builtin | Description |
|---|---|
| `echo` | Afficher des arguments (builtin interne) |
| `exit [code]` | Quitter avec code de retour |
| `set` | Variables locales / liste toutes les variables |
| `unset` | Supprime une variable locale |
| `alias` | Définit / liste les aliases |
| `unalias` | Supprime un alias |
| `history` | Affiche l'historique |

#### Signaux

| Signal | Etat |
|---|---|
| `SIGINT` (Ctrl+C) | Partiellement géré (interrompt le processus enfant) |
| `SIGQUIT` (Ctrl+\) | Non géré explicitement |
| `SIGTSTP` (Ctrl+Z) | Non implémenté (job control) |
| `SIGCHLD` | Non implémenté (nécessaire pour job control) |
| `SIGHUP` | Non implémenté |

---

### Bonus (non commencé)

| Feature |
|---|
| `foreach`, `while`, `if/else/endif` |
| Complétion avancée (options, man pages) |
| Prompt personnalisable `$prompt` |
| `source` / `.` |
| Historique persistant `~/.history` |
| `pushd` / `popd` / `dirs` |
| Expansion `~user` |
| `$path` comme array tcsh-style |

---

## Ordre d'expansion (référence tcsh)

1. History (`!`, `!!`, `!n`)
2. Aliases
3. Parsing / tokenisation
4. Variables (`$var`, `$$`, etc.)
5. Backticks (`` `cmd` ``)
6. Globbing (`*`, `?`, `[`, `]`)

---

## Points de vigilance

- Aucune fuite mémoire tolérée — valider avec Valgrind.
- Compilation sans warning avec `-Wall -Wextra`.
- Ne jamais casser une feature qui marche pour en ajouter une nouvelle.
- Tout comportement doit être identique à `tcsh` (codes de retour, messages d'erreur).
- `make re` doit recompiler depuis zéro.
- Ne pas livrer de fichiers `.o`, binaires ou temporaires.
