# Flux D Execution

Ce document decrit pas a pas le runtime du minishell.

## 1. Boucle Principale

Fichier: `src/core/main.c`

- initialise `main_t` via `init_main`;
- lit la ligne utilisateur;
- normalise la fin de ligne;
- appelle `execute_command`;
- conserve le dernier status de sortie.

## 2. Dispatch Niveau Ligne

Fichier: `src/execution/dispatch/execute_command.c`

- split la ligne par `;`;
- pour chaque sous-commande:
  - si presence de `|`: envoie a `execute_pipeline`;
  - sinon: envoie a `execute_single_command`.

## 3. Commande Simple

Fichier: `src/execution/dispatch/execute_single_command.c`

- parse vers `command_ctx_t`;
- tente un builtin via registre;
- sinon execute en externe (`exec_any`);
- nettoie le contexte avant retour.

## 4. Dispatch Builtins

Fichier: `src/execution/dispatch/execute_builtin.c`

- table `builtin_command_t` (`name` + handler);
- comparaison du nom de commande;
- execution du handler correspondant;
- `-1` si commande non builtin.

## 5. Execution Externe

Fichiers:

- `src/execution/external/exec_any.c`
- `src/execution/external/run_fork.c`
- `src/execution/external/exec_error_case.c`

Etapes:

1. resolution du binaire (commande absolue/relative ou PATH)
2. construction envp temporaire
3. `fork`
4. enfant: redirection puis `execve`
5. parent: `waitpid` et normalisation status

## 6. Redirections

Fichier: `src/execution/redirection/apply_redirection.c`

- detecte l index du token (`>`, `>>`, `<`)
- ouvre le fd cible
- bind `dup2` sur stdin/stdout
- coupe `argv` au niveau du token de redirection

## 7. Pipeline

Fichiers:

- `src/execution/pipeline/pipeline_parse.c`
- `src/execution/pipeline/pipeline_spawn.c`
- `src/execution/pipeline/pipeline_wait.c`
- `src/execution/pipeline/pipeline_execute.c`

Etapes:

1. validation syntaxique des pipes
2. parsing en `pipeline_segment_t[]`
3. allocation `pids`
4. creation des pipes intermediaires
5. spawn de chaque segment
6. attente et retour du status du dernier segment
7. cleanup global de l etat pipeline

## 8. Builtins Env/Fs

- `builtin_env`: affiche la liste `stock_env`
- `builtin_setenv`: ajoute/met a jour une variable
- `builtin_unsetenv`: supprime une variable
- `builtin_cd`: change de repertoire et gere `old_path`

## 9. Gestion Des Erreurs

- erreurs parsing: status non nul immediate
- erreurs fork/exec: status conforme shell
- erreurs signaux (segfault/fpe): normalisation via `get_seg`

## 10. Invariants Runtime

- un `command_ctx_t` est toujours nettoye en fin de commande simple
- un `pipeline_state_t` est toujours libere en succes/erreur
- aucune commande externe ne doit dependre de champs temporaires globaux
