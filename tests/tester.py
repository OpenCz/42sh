#!/usr/bin/env python3
"""Functional test runner comparing 42sh to tcsh with a nicer UI."""

import argparse
import difflib
import os
import re
import subprocess
import sys
from dataclasses import dataclass
from typing import List, Optional

ANSI_RESET = "\033[0m"
ANSI_BOLD = "\033[1m"
ANSI_RED = "\033[31m"
ANSI_GREEN = "\033[32m"
ANSI_YELLOW = "\033[33m"
ANSI_CYAN = "\033[36m"
ANSI_MAGENTA = "\033[35m"

TEST_FILE = os.path.join(os.path.dirname(__file__), "test")
DEFAULT_SHELL = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "42sh"))
REFERENCE_SHELL = "/bin/tcsh"
ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
LOG_DIR = os.path.join(ROOT_DIR, "Logs", "functional_tests")


@dataclass
class TestCase:
    test_id: str
    name: str
    setup: str
    clean: str
    tcsh_update: str
    tests: List[str]


@dataclass
class TestResult:
    ok: bool
    missing: List[str]
    my_out: str
    ref_out: str
    diff_lines: List[str]


def color(text: str, code: str) -> str:
    if not sys.stdout.isatty():
        return text
    return f"{code}{text}{ANSI_RESET}"


def header() -> None:
    line = "=" * 74
    print(color(line, ANSI_CYAN))
    print(color("42sh Functional Tests", ANSI_BOLD))
    print(color("Comparing against tcsh", ANSI_MAGENTA))
    print(color(line, ANSI_CYAN))


def parse_tests(path: str) -> List[TestCase]:
    tests: List[TestCase] = []
    current_id: Optional[str] = None
    current: dict = {}
    in_tests = False

    with open(path, "r", encoding="utf-8") as handle:
        for raw in handle:
            line = raw.rstrip("\n")
            start_match = re.match(r"^\[(\d+)\]$", line)
            end_match = re.match(r"^\[(\d+)-END\]$", line)

            if start_match:
                current_id = start_match.group(1)
                current = {
                    "name": "",
                    "setup": "",
                    "clean": "",
                    "tcsh_update": "",
                    "tests": [],
                }
                in_tests = False
                continue

            if end_match and current_id == end_match.group(1):
                tests.append(
                    TestCase(
                        test_id=current_id,
                        name=current.get("name", ""),
                        setup=current.get("setup", ""),
                        clean=current.get("clean", ""),
                        tcsh_update=current.get("tcsh_update", ""),
                        tests=current.get("tests", []),
                    )
                )
                current_id = None
                current = {}
                in_tests = False
                continue

            if current_id is None:
                continue

            if line.startswith("NAME="):
                current["name"] = line.split("=", 1)[1].strip().strip('"')
                continue
            if line.startswith("SETUP="):
                current["setup"] = line.split("=", 1)[1].strip().strip('"')
                continue
            if line.startswith("CLEAN="):
                current["clean"] = line.split("=", 1)[1].strip().strip('"')
                continue
            if line.startswith("TCSHUPDATE="):
                current["tcsh_update"] = line.split("=", 1)[1].strip().strip('"')
                continue
            if line.startswith("TESTS="):
                in_tests = True
                continue

            if in_tests:
                current["tests"].append(line)

    return tests


def write_test_script(lines: List[str], path: str) -> None:
    with open(path, "w", encoding="utf-8") as handle:
        handle.write("#!/bin/bash\n")
        for line in lines:
            handle.write(line + "\n")
    os.chmod(path, 0o755)


def build_run_command(setup: str, clean: str, test_script: str, shell_cmd: str) -> str:
    parts = []
    if setup:
        parts.append(setup)
    parts.append(f"{test_script} | {shell_cmd} ; echo Shell exit with code $?")
    if clean:
        parts.append(clean)
    return "; ".join(parts)


def run_shell(command: str) -> str:
    result = subprocess.run(
        command,
        shell=True,
        executable="/bin/bash",
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    return result.stdout


def normalize_output(output: str) -> List[str]:
    lines = output.splitlines()
    filtered = []
    for line in lines:
        if line.startswith("_="):
            continue
        if line.startswith("[1]"):
            continue
        filtered.append(line)
    return filtered


def compare_outputs(reference: List[str], actual: List[str]) -> List[str]:
    missing = []
    for line in reference:
        if line not in actual:
            missing.append(line)
    return missing


def progress_bar(done: int, total: int) -> str:
    width = 30
    if total == 0:
        return "[" + ("-" * width) + "]"
    filled = int(width * done / total)
    return "[" + ("#" * filled) + ("-" * (width - filled)) + "]"


def print_diff(reference: List[str], actual: List[str], limit: int = 200) -> List[str]:
    diff = list(
        difflib.unified_diff(
            reference,
            actual,
            fromfile="tcsh",
            tofile="42sh",
            lineterm="",
        )
    )
    if not diff:
        return []
    print(color("\nDiff (tcsh vs 42sh):", ANSI_YELLOW))
    for line in diff[:limit]:
        if line.startswith("+") and not line.startswith("+++"):
            print(color(line, ANSI_GREEN))
        elif line.startswith("-") and not line.startswith("---"):
            print(color(line, ANSI_RED))
        else:
            print(line)
    if len(diff) > limit:
        print(color("... diff truncated ...", ANSI_YELLOW))
    return diff


def init_logs() -> tuple[str, str]:
    os.makedirs(LOG_DIR, exist_ok=True)
    timestamp = subprocess.check_output(["date", "+%Y-%m-%d_%H-%M-%S"], text=True).strip()
    global_log = os.path.join(LOG_DIR, f"run_{timestamp}.log")
    latest_log = os.path.join(LOG_DIR, "latest.log")
    with open(global_log, "w", encoding="utf-8") as handle:
        handle.write("=" * 64 + "\n")
        handle.write(f"Functional Tests — {timestamp}\n")
        handle.write(f"Shell   : {DEFAULT_SHELL}\n")
        handle.write(f"Reference: {REFERENCE_SHELL}\n")
        handle.write("=" * 64 + "\n\n")
    return global_log, latest_log


def write_failure_artifacts(test_id: str, my_out: str, ref_out: str, diff_lines: List[str]) -> None:
    test_log_dir = os.path.join(LOG_DIR, test_id)
    os.makedirs(test_log_dir, exist_ok=True)
    with open(os.path.join(test_log_dir, "mysh.out"), "w", encoding="utf-8") as handle:
        handle.write(my_out)
    with open(os.path.join(test_log_dir, "tcsh.out"), "w", encoding="utf-8") as handle:
        handle.write(ref_out)
    if diff_lines:
        with open(os.path.join(test_log_dir, "diff.txt"), "w", encoding="utf-8") as handle:
            handle.write("\n".join(diff_lines))


def print_block(title: str, content: str, color_code: str) -> None:
    lines = content.splitlines() or [""]
    width = max(len(title), max(len(line) for line in lines))
    border = "+" + ("-" * (width + 2)) + "+"
    print(color(border, color_code))
    print(color(f"| {title.ljust(width)} |", color_code))
    print(color(border, color_code))
    for line in lines:
        print(color(f"| {line.ljust(width)} |", color_code))
    print(color(border, color_code))


def run_test(
    case: TestCase,
    test_script: str,
    shell_path: str,
    ref_shell: str,
    debug: int,
    pid: int,
) -> TestResult:
    my_cmd = build_run_command(case.setup, case.clean, test_script, shell_path)
    tcsh_setup = case.setup
    if case.tcsh_update:
        tcsh_setup = "; ".join([c for c in [case.setup, case.tcsh_update] if c])
    ref_cmd = build_run_command(tcsh_setup, case.clean, test_script, f"{ref_shell} -f")

    my_out = run_shell(my_cmd)
    ref_out = run_shell(ref_cmd)

    shell_file = f"/tmp/.shell.{pid}"
    ref_file = f"/tmp/.refer.{pid}"
    with open(shell_file, "w", encoding="utf-8") as handle:
        handle.write(my_out)
    with open(ref_file, "w", encoding="utf-8") as handle:
        handle.write(ref_out)

    normalized_ref = normalize_output(ref_out)
    normalized_my = normalize_output(my_out)
    missing = compare_outputs(normalized_ref, normalized_my)

    ok = len(missing) == 0
    if not ok:
        fail_dir = f"/tmp/test.{pid}/{case.test_id}"
        os.makedirs(fail_dir, exist_ok=True)
        with open(os.path.join(fail_dir, "mysh.out"), "w", encoding="utf-8") as handle:
            handle.write(my_out)
        with open(os.path.join(fail_dir, "tcsh.out"), "w", encoding="utf-8") as handle:
            handle.write(ref_out)

    diff_lines: List[str] = []
    if not ok and debug >= 1:
        print(color("Missing lines from 42sh output:", ANSI_YELLOW))
        for line in missing[:20]:
            print(color(f"- {line}", ANSI_RED))
        if len(missing) > 20:
            print(color("... missing list truncated ...", ANSI_YELLOW))
        diff_lines = print_diff(normalized_ref, normalized_my)

    if debug >= 2:
        print(color("Output 42sh:", ANSI_YELLOW))
        print(my_out.rstrip())
        print(color("Output tcsh:", ANSI_YELLOW))
        print(ref_out.rstrip())

    return TestResult(ok=ok, missing=missing, my_out=my_out, ref_out=ref_out, diff_lines=diff_lines)


def main() -> int:
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument("-d", dest="debug", action="store_true")
    parser.add_argument("--debug", dest="debug", action="store_true")
    parser.add_argument("-s", dest="summary", action="store_true")
    parser.add_argument("--summary", dest="summary", action="store_true")
    parser.add_argument("id", nargs="?")
    args, _ = parser.parse_known_args()

    if not os.path.isfile(TEST_FILE):
        print(color(f"No tests file at {TEST_FILE}", ANSI_RED), file=sys.stderr)
        return 1

    if not os.path.isfile(DEFAULT_SHELL):
        print(color(f"{DEFAULT_SHELL} not found", ANSI_RED), file=sys.stderr)
        return 1

    if not os.path.isfile(REFERENCE_SHELL):
        print(color(f"{REFERENCE_SHELL} not found", ANSI_RED), file=sys.stderr)
        return 1

    test_list = parse_tests(TEST_FILE)
    if args.id:
        test_list = [t for t in test_list if t.test_id == args.id]
    if not test_list:
        print(color("No matching tests to run.", ANSI_RED), file=sys.stderr)
        return 1

    debug_level = 2 if args.debug else 1
    header()
    total = len(test_list)
    passed = 0
    failed: List[tuple[TestCase, TestResult]] = []
    pid = os.getpid()
    tmp_test_script = f"/tmp/.tester.{pid}"
    global_log, latest_log = init_logs()

    try:
        for index, case in enumerate(test_list, start=1):
            write_test_script(case.tests, tmp_test_script)
            result = run_test(case, tmp_test_script, DEFAULT_SHELL, REFERENCE_SHELL, debug_level, pid)
            status = color("OK", ANSI_GREEN) if result.ok else color("KO", ANSI_RED)
            print(f"{case.test_id} {case.name} : {status}")
            with open(global_log, "a", encoding="utf-8") as handle:
                handle.write(f"Test {case.test_id} ({case.name}) : {'OK' if result.ok else 'KO'}\n")
            if result.ok:
                passed += 1
            else:
                failed.append((case, result))
                write_failure_artifacts(case.test_id, result.my_out, result.ref_out, result.diff_lines)
            if sys.stdout.isatty():
                bar = progress_bar(index, total)
                percent = int((index / total) * 100)
                print(f"{bar} {index}/{total} ({percent}%)")
    finally:
        if os.path.exists(tmp_test_script):
            os.unlink(tmp_test_script)

    percent = int((passed * 100) / total) if total else 0
    color_code = ANSI_GREEN if percent >= 90 else ANSI_YELLOW if percent >= 60 else ANSI_RED
    print(color("=" * 74, ANSI_CYAN))
    print(
        color(
            f"Tests completed: {passed}/{total} tests passed ({percent}%)",
            color_code,
        )
    )
    print(color("=" * 74, ANSI_CYAN))

    with open(global_log, "a", encoding="utf-8") as handle:
        handle.write(f"\nSUMMARY: {passed}/{total} passed ({percent}%)\n")
        if failed:
            handle.write("Failed tests: " + " ".join(case.test_id for case, _ in failed) + "\n")

    try:
        if os.path.exists(latest_log):
            os.remove(latest_log)
        os.symlink(global_log, latest_log)
    except OSError:
        pass

    if failed and not args.summary:
        print(color("\nFailed Tests Details:", ANSI_YELLOW))
        for case, result in failed:
            print(color("-" * 74, ANSI_CYAN))
            print(color(f"Test {case.test_id}: {case.name}", ANSI_BOLD))
            print_block("42sh output", result.my_out.rstrip(), ANSI_CYAN)
            print_block("tcsh output", result.ref_out.rstrip(), ANSI_GREEN)
            if result.diff_lines:
                print_block("diff (tcsh vs 42sh)", "\n".join(result.diff_lines[:200]), ANSI_YELLOW)

    return 0 if passed == total else 1


if __name__ == "__main__":
    sys.exit(main())

