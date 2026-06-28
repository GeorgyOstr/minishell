#!/bin/bash

cleanup()
{
	rm -f in.txt out.txt
}

echo "========== prepare =========="
echo "hello" > in.txt
echo "world" >> in.txt

echo
echo "========== input redirect (<) =========="
echo "cat < in.txt"
echo "----------------------------"
echo "cat < in.txt" | ./minishell
echo

echo
echo "========== output redirect (>) =========="
echo "echo minishell > out.txt"
echo "cat out.txt"
echo "----------------------------"
echo "echo minishell > out.txt
cat out.txt" | ./minishell
echo

echo
echo "========== overwrite test (>) =========="
echo "echo first > out.txt"
echo "echo second > out.txt"
echo "cat out.txt"
echo "----------------------------"
echo "echo first > out.txt
echo second > out.txt
cat out.txt" | ./minishell
echo

echo
echo "========== heredoc (<<) =========="
echo "cat << EOF"
echo "----------------------------"
printf "cat << EOF\nhello\nworld\nEOF\n" | ./minishell
echo

echo "========== no such file =========="
echo "cat < nofile"
echo "----------------------------"
echo "cat < nofile" | ./minishell
echo

cleanup

echo
echo "all tests finished"