#!/bin/bash

cleanup()
{
	rm -f bash_out mini_out
}

assert()
{
	printf '%-35s:' "\"$1\""

	printf "%b" "$1" | bash >bash_out 2>/dev/null
	bash_status=$?

	printf "%b" "$1" | ./minishell >mini_out 2>/dev/null
	mini_status=$?

	if diff bash_out mini_out >/dev/null; then
		echo -n " output OK"
	else
		echo -n " output NG"
	fi

	if [ "$bash_status" = "$mini_status" ]; then
		echo " status OK"
	else
		echo " status NG (bash=$bash_status mini=$mini_status)"
	fi
}

assert_contains()
{
	printf '%-35s:' "\"$1\""

	printf "%b" "$1" | ./minishell >mini_out 2>/dev/null
	mini_status=$?

	if grep "$2" mini_out >/dev/null; then
		echo -n " output OK"
	else
		echo -n " output NG"
	fi

	if [ "$mini_status" = "$3" ]; then
		echo " status OK"
	else
		echo " status NG (expected=$3 mini=$mini_status)"
	fi
}

assert_not_contains()
{
	printf '%-35s:' "\"$1\""

	printf "%b" "$1" | ./minishell >mini_out 2>/dev/null
	mini_status=$?

	if grep "$2" mini_out >/dev/null; then
		echo -n " output NG"
	else
		echo -n " output OK"
	fi

	if [ "$mini_status" = "$3" ]; then
		echo " status OK"
	else
		echo " status NG (expected=$3 mini=$mini_status)"
	fi
}

echo "========== echo =========="
assert "echo\n"
assert "echo hello\n"
assert "echo hello world\n"
assert "echo -n hello\n"
assert "echo -nnnn hello\n"

echo
echo "========== pwd =========="
assert "pwd\n"

echo
echo "========== env =========="
assert_contains "env\n" "PATH=" 0
assert_contains "env\n" "HOME=" 0

echo
echo "========== export =========="
assert_contains "export\n" "declare -x PATH=" 0
assert_contains "export TEST=42\nenv\n" "TEST=42" 0
assert_contains "export TEST=hello\nenv\n" "TEST=hello" 0
assert "export 1ABC=42\n"

echo
echo "========== unset =========="
assert_not_contains "export TEST=42\nunset TEST\nenv\n" "TEST=" 0

echo
echo "========== cd =========="
assert "pwd\ncd ..\npwd\n"
assert "cd /\n"
assert "cd no_such_directory\n"

echo
echo "========== exit =========="
assert "exit\n"
assert "exit 42\n"

cleanup
echo
echo "Done."