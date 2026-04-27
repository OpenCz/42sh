#!/usr/bin/env bash

set -euo pipefail

show_help() {
    cat <<EOF
Usage: $0 [REPOSITORY]

Check a repository compliance with Banana C-O1 and C-O4 rules.

IT MUST BE RUN FROM THE REPOSITORY ROOT.

REPOSITORY:
    Repository to check (default: current directory)

EXAMPLES:
    $0                   # Check current directory
    $0 /path/to/repo     # Check specific repository

EXIT CODES:
    0    No infractions found
    1    At least one infraction found
EOF
}

while [[ $# -gt 0 ]]; do
    case $1 in
    -h | --help)
        show_help
        exit 0
        ;;
    -*)
        echo "Error: Unknown option $1"
        echo "Use -h or --help for usage information"
        exit 1
        ;;
    *)
        SEARCH_DIR="$1"
        shift
        ;;
    esac
done

SEARCH_DIR="${SEARCH_DIR:-.}"

if [[ ! -d "$SEARCH_DIR" ]]; then
    echo "Error: Directory '$SEARCH_DIR' does not exist"
    exit 1
fi

IGNORED_DIRECTORIES=(
    "./.git"
    "./tests"
    "./bonus"
)

FIND_PRUNE=""
for dir in "${IGNORED_DIRECTORIES[@]}"; do
    FIND_PRUNE+="-path $dir -o "
done
FIND_PRUNE="${FIND_PRUNE::-3}"

is_unwanted_binary() {
    local file="$1"

    local magic_bytes
    if [[ -f "$file" ]]; then
        magic_bytes=$(head -c 4 "$file" 2>/dev/null | xxd -p 2>/dev/null || echo "")

        # ELF: 7f454c46
        # EXE/MZ: 4d5a
        # Mach-O: feedface
        if [[ "$magic_bytes" =~ ^(7f454c46|4d5a|feedface) ]]; then
            return 0
        fi
    fi

    return 1
}

# Inspired by
# https://github.com/github/gitignore/blob/master/C.gitignore
# https://github.com/github/gitignore/blob/master/Gcov.gitignore
is_unwanted_file() {
    local filename="$1"

    # Prerequisites
    [[ "$filename" =~ \.d$ ]] && return 0

    # Object files
    [[ "$filename" =~ \.(o|ko|obj|elf)$ ]] && return 0

    # Linker output
    [[ "$filename" =~ \.(ilk|map|exp)$ ]] && return 0

    # Precompiled Headers
    [[ "$filename" =~ \.(gch|pch)$ ]] && return 0

    # Libraries
    [[ "$filename" =~ \.(lib|a|la|lo)$ ]] && return 0

    # Shared objects (inc. Windows DLLs)
    [[ "$filename" =~ \.(dll|so|dylib)$ ]] && return 0
    [[ "$filename" =~ \.so\..*$ ]] && return 0

    # Executables
    [[ "$filename" =~ \.(exe|out|app|hex)$ ]] && return 0
    [[ "$filename" =~ \.i.*86$ ]] && return 0
    [[ "$filename" =~ \.x86_64$ ]] && return 0

    # Debug files
    [[ "$filename" =~ \.(su|idb|pdb)$ ]] && return 0

    # Kernel Module Compile Results
    [[ "$filename" =~ \.mod.*$ ]] && return 0
    [[ "$filename" =~ \.cmd$ ]] && return 0
    [[ "$filename" =~ ^modules\.order$ ]] && return 0
    [[ "$filename" =~ ^Module\.symvers$ ]] && return 0
    [[ "$filename" =~ ^Mkfile\.old$ ]] && return 0
    [[ "$filename" =~ ^dkms\.conf$ ]] && return 0

    # gcc coverage testing tool files
    [[ "$filename" =~ \.(gcno|gcda|gcov)$ ]] && return 0

    # Temporary files
    [[ "$filename" =~ ~.* ]] && return 0
    [[ "$filename" =~ \#.* ]] && return 0

    # Valgrind core dump files
    [[ "$filename" =~ ^vgcore\.[0-9]+$ ]] && return 0

    return 1
}

is_c_file() {
    local file="$1"
    [[ "$file" =~ \.(c|h)$ ]]
}

get_filename_without_extension() {
    local file="$1"
    local filename
    filename=$(basename "$file")
    echo "${filename%.*}"
}

get_filename() {
    basename "$1"
}

check_repo() {
    echo "Checking delivery files in $SEARCH_DIR"

    local found_infractions=false

    while IFS= read -r -d '' file; do
        local filename
        filename=$(get_filename "$file")

        if is_unwanted_binary "$file"; then
            echo "$file: [Banana] [Major] unwanted binary file (C-O1)"
            found_infractions=true
            continue
        elif is_unwanted_file "$filename"; then
            echo "$file: [Banana] [Major] unwanted file (C-O1)"
            found_infractions=true
        fi
        if is_c_file "$file"; then
            local file_name
            file_name=$(get_filename_without_extension "$file")

            if [[ ! "$file_name" =~ ^[a-z]([a-z0-9_]*[a-z0-9])?$ ]] || [[ "$file_name" =~ __ ]]; then
                echo "$file: [Banana] [Minor] invalid file name (C-O4)"
                found_infractions=true
            fi
        fi
    done < <(find "$SEARCH_DIR" \( $FIND_PRUNE \) -prune -o -type f -print0)

    if [[ "$found_infractions" == "true" ]]; then
        exit 1
    fi
    echo "No infractions found"
    exit 0
}

check_repo
