#!/bin/env python3

import sys, re, os

TYPES = ['doc', 'feat', 'fix', 'style', 'test', 'chore', 'ci']
REGEXP = "^[.0-9]+$|^([Rr]evert|[Mm]erge):? .*$|^("

def build_regex():
    global REGEXP
    global TYPES
    for type in TYPES:
        REGEXP += type + "|"
    REGEXP = REGEXP[:-1]
    REGEXP += ")(\(.+\))?: "

def get_commit_message():
    commit_message = ""
    with open(sys.argv[1], "r") as f:
        commit_message = f.readline()
    return commit_message

def print_error(commit_message):
    os.system("echo '\n\e[31m[Invalid Commit Message]'")
    os.system("echo '------------------------\033[0m\e[0m'")
    os.system("echo 'Valid types: \e[36m{}\033[0m'".format(TYPES))
    os.system("echo '\e[37mActual commit message: \e[33m\"{}\"\033[0m'".format(commit_message[:-1]))
    os.system("echo '\e[37mExample valid commit message: \e[36m\"fix(subject): message\"\033[0m'")
    os.system("echo '\e[37mRegex: \e[33m\"{}\"\033[0m\n'".format(REGEXP))

if __name__ == "__main__":
    commit_message = get_commit_message()
    build_regex()
    if not re.match(REGEXP, commit_message):
        print_error(commit_message)
        sys.exit(1)
    sys.exit(0)
