# Architecture Du Projet

Ce document decrit l architecture actuelle du minishell et les regles de conception
qui permettent de garder une base modulaire, lisible et facile a faire evoluer.

## 1. Vision D Ensemble

Le projet est decoupe par responsabilite metier:

- `src/core`: cycle de vie global du shell et contexte de commande.
- `src/builtins`: commandes internes (`env`, `setenv`, `unsetenv`, `cd`).
- `src/execution`: orchestration d execution (dispatch, externe, pipeline, redirections).
- `src/environment`: acces a l environnement et resolution binaire via PATH.
- `src/parsing`: extraction de tokens de parsing (ex: redirection).
- `src/utils`: fonctions utilitaires bas niveau (string, io, validation).
- `src/memory`: destruction/liberation des structures dynamiques.

Le dossier `include` suit la meme logique avec des APIs separees par domaines.

## 2. Arborescence Detaillee

### 2.1 Core

- `src/core/main.c`: boucle REPL, lecture entree, appel executeur.
- `src/core/init/init_env.c`: construction de la liste chainee d environnement.
- `src/core/init/init_main.c`: initialisation de l etat global `main_t`.
- `src/core/context/command_context.c`: parsing d une commande vers `command_ctx_t`.

### 2.2 Builtins

- `src/builtins/env/my_env.c`: affichage de l environnement.
- `src/builtins/env/my_setenv.c`: ajout/mise a jour variable env.
- `src/builtins/env/my_unsetenv.c`: suppression variable env.
- `src/builtins/fs/my_chdir.c`: implementation de `cd`.

### 2.3 Execution

- `src/execution/dispatch/execute_command.c`: split par `;` et orchestration globale.
- `src/execution/dispatch/execute_single_command.c`: pipeline hors `|`, builtin/externe.
- `src/execution/dispatch/execute_builtin.c`: registre et dispatch des builtins.
- `src/execution/external/exec_any.c`: resolution commande et lancement externe.
- `src/execution/external/run_fork.c`: fork + wait + status.
- `src/execution/external/exec_error_case.c`: gestion erreurs `execve` et signaux.
- `src/execution/pipeline/*`: parse/spawn/wait/finalize pour les pipelines.
- `src/execution/redirection/apply_redirection.c`: application des redirections.

### 2.4 Environment

- `src/environment/query/get_home.c`: lecture de HOME.
- `src/environment/query/get_path.c`: lecture de PATH.
- `src/environment/path/check_bin.c`: resolution executable dans PATH.

### 2.5 Parsing

- `src/parsing/redirection/get_redirection.c`: detection token de redirection.

### 2.6 Utils

- `src/utils/strings/*`: fonctions string maison.
- `src/utils/io/my_putstr.c`: sorties stdout/stderr.
- `src/utils/validation/*`: validation des arguments.

### 2.7 Memory

- `src/memory/free/free_function.c`: liberation des structures dynamiques.

## 3. Types Structurants

Les types centraux sont declares dans `include/core/types.h`:

- `env_t`: noeud de liste chainee `key/value` pour l environnement.
- `main_t`: etat global du shell (longue duree).
- `command_ctx_t`: etat ephemere d une commande.
- `pipeline_segment_t`: representation d un segment de pipeline.
- `pipeline_state_t`: contexte d execution d un pipeline.

## 4. Frontieres Modulaires

Regles clefs de modularite:

- Les modules `dispatch` ne font pas de logique metier de redirection.
- Les modules `external` ne parsent pas la commande; ils consomment un contexte deja valide.
- Les builtins sont appeles via un registre (`builtin_command_t`) et une signature commune.
- Le parsing de redirection est isole du code de fork/exec.
- Le pipeline est traite comme une unite independante avec son propre etat.

## 5. Flux D Execution

Chemin nominal:

1. `main` lit une ligne.
2. `execute_command` split la ligne sur `;`.
3. Chaque segment va soit vers `execute_pipeline` soit `execute_single_command`.
4. `execute_single_command` parse `command_ctx_t`.
5. Si builtin connu: execute handler builtin.
6. Sinon: `exec_any` -> `run_fork` -> `child_exec`.
7. Retour du status au REPL.

## 6. APIs Header Par Domaine

Les points d entree publics sont separes:

- `include/core/core.h`
- `include/builtins/builtins.h`
- `include/execution/execution.h`
- `include/environment/environment.h`
- `include/parsing/parsing.h`
- `include/utils/utils.h`
- `include/memory/memory.h`

Le fichier `include/42sh.h` sert de facade agregatrice pour compatibilite.

## 7. Evolutions Recommandees

Pour rester modulaire a long terme:

- Ajouter chaque nouvelle feature dans un sous-domaine existant ou nouveau,
  jamais dans un fichier fourre-tout.
- Garder les fonctions `static` quand elles ne sont pas exportees.
- Limiter la taille des fonctions et separer parse, validation, execution.
- Documenter toute nouvelle structure dans `docs/OWNERSHIP.md`.
- Ajouter au minimum un test unitaire par nouveau chemin de code critique.

## 8. Checklist Avant Merge

- Le module a un domaine clair (`core`, `execution`, `builtins`, etc.).
- Le header exporte seulement ce qui est necessaire.
- Le code ne depend pas d un champ global quand un contexte local existe.
- Les allocations ont un destructeur explicite.
- `make re` et `make unit_tests` passent.
