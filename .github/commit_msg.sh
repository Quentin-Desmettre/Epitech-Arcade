#!/bin/env python3

#config_file_name="conventional-commits.json"

# checks that jq is usable
#function check_jq_exists_and_executable {
#if ! [ -x "$(command -v jq)" ]; then
#  echo -e "\`commit-msg\` hook failed. Please install jq."
#  exit 1
#fi
#}

import sys, re

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
    print("\n\e[31m[Invalid Commit Message]")
    print("------------------------\033[0m\e[0m")
    print("Valid types: \e[36m{}\033[0m".format(TYPES))
    print("\e[37mActual commit message: \e[33m\"{}\"\033[0m".format(commit_message))
    print("\e[37mExample valid commit message: \e[36m\"fix(subject): message\"\033[0m")
    print("\e[37mRegex: \e[33m\"{}\"\033[0m".format(REGEXP))

if __name__ == "__main__":
    commit_message = get_commit_message()
    build_regex()
    if not re.match(REGEXP, commit_message):
        print_error(commit_message)
        sys.exit(1)
    sys.exit(0)
