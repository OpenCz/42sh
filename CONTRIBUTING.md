# Contributing to 42sh

Welcome to **42sh** — a tcsh-compatible shell written in C.
This document describes the conventions and workflow used by the team.

---

## Table of Contents

- [Branching Strategy](#branching-strategy)
- [Commit Convention](#commit-convention)
- [Pull Requests](#pull-requests)
- [Code Review](#code-review)
- [Linking Issues](#linking-issues)
- [Coding Standards](#coding-standards)

---

## Branching Strategy

All work is done on feature branches. **Never commit directly to `main`.**

**Branch naming:**

```
feature/<short-description>
```

Examples:

```
feature/builtin-cd
feature/pipe-support
feature/lexer-refactor
```

Keep the description short, lowercase, and hyphen-separated.

---

## Commit Convention

We follow [Conventional Commits](https://www.conventionalcommits.org/).

**Format:**

```
<type>: <short description>
```

**Types:**

| Type | When to use |
|------|-------------|
| `feat` | A new feature |
| `fix` | A bug fix |
| `chore` | Maintenance, tooling, config |
| `refactor` | Code restructuring without behavior change |
| `docs` | Documentation only |
| `test` | Adding or fixing tests |
| `style` | Formatting, missing semicolons, etc. |

**Examples:**

```
feat: add cd builtin with OLDPWD support
fix: handle empty pipe input without crash
refactor: split lexer into tokenizer and parser
docs: update README with build instructions
```

- Use the **imperative mood** ("add", not "added" or "adds")
- Keep the subject line under 72 characters
- No period at the end

---

## Pull Requests

1. Make sure your branch is up to date with `main` before opening a PR
2. Open a PR from your feature branch targeting `main`
3. Fill in the PR description — what it does, why, and any relevant notes
4. **Link the PR to its corresponding issue** (see [Linking Issues](#linking-issues))
5. Assign at least one reviewer

**A PR must not be merged by its own author.**

---

## Code Review

- At least **1 approval** is required before merging
- Address all review comments before requesting a re-review
- Reviewers should respond within a reasonable time — if blocked, ping on the team channel
- Prefer **squash merge** to keep the history clean

**Reviewer checklist:**
- Does the code respect Epitech norms? (20-line functions, 4 params max, no forbidden stdlib)
- Is the logic clear and documented where needed?
- Does it break any existing behavior?

---

## Linking Issues

Every PR should be linked to a GitHub issue using a closing keyword in the PR description:

```
Closes #42
Fixes #17
```

This automatically closes the issue when the PR is merged and keeps the
milestone progress up to date.

---

## Coding Standards

This project follows **Epitech coding norms**:

- Functions must not exceed **20 lines**
- Functions must not take more than **4 parameters**
- No use of the standard library beyond `write`, `malloc`, and authorized functions
- One function per file where applicable
- No global variables unless explicitly justified

Any PR that violates these norms will be rejected during review.
