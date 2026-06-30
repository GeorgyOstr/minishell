#!/bin/bash

make || exit 1

echo "===== simple command ====="
echo "ls" | ./minishell

echo "===== command with args ====="
echo "ls -l" | ./minishell

echo "===== single pipe ====="
echo "ls | wc" | ./minishell

echo "===== multiple pipes ====="
echo "ls | grep a | wc" | ./minishell

echo "===== redirect out ====="
echo "echo hello > out.txt" | ./minishell

echo "===== redirect in ====="
echo "cat < in.txt" | ./minishell

echo "===== append ====="
echo "echo hello >> out.txt" | ./minishell

echo "===== heredoc token ====="
echo "cat << EOF" | ./minishell
