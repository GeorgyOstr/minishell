#!/bin/bash

make re || exit 1

run()
{
	echo "===== $1 ====="
	echo "$1" | ./minishell
	echo
}

run "ls -l | grep a > out.txt"
run "asd|asdf>afwe>>><<<afwe,<"
run "cat<infile"
run "echo hello>>out.txt"
run "cat<<EOF"
run "| ls"
run "ls |"
run "ls || grep"
run "echo hello >"
run "echo hello <"
run "echo 'a|b'"
run 'echo "a|b"'
run "echo a b c"