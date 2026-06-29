#!/bin/bash

MINISHELL=./minishell
TMP_DIR=.tmp_pipe_heredoc_test
BASH_OUT=$TMP_DIR/bash_out
MINI_OUT=$TMP_DIR/mini_out
BASH_ERR=$TMP_DIR/bash_err
MINI_ERR=$TMP_DIR/mini_err
TOTAL=0
OK=0
NG=0

setup()
{
	if [ ! -x "$MINISHELL" ]; then
		echo "Error: ./minishell not found or not executable"
		echo "Run this script from the project root after make."
		exit 1
	fi
	rm -rf "$TMP_DIR"
	mkdir "$TMP_DIR"
}

cleanup_files()
{
	rm -f "$TMP_DIR"/out_pipe
	rm -f "$TMP_DIR"/out_heredoc
	rm -f "$TMP_DIR"/out_mix
	rm -f "$TMP_DIR"/infile
}

run_bash()
{
	input=$1
	(
		cd "$TMP_DIR" || exit 1
		printf "%b" "$input" | bash >bash_out 2>bash_err
	)
	BASH_STATUS=$?
}

run_mini()
{
	input=$1
	(
		cd "$TMP_DIR" || exit 1
		printf "%b" "$input" | ../minishell >mini_out 2>mini_err
	)
	MINI_STATUS=$?
}

print_result()
{
	name=$1
	TOTAL=$((TOTAL + 1))
	printf '%-38s' "$name"
	if diff -u "$BASH_OUT" "$MINI_OUT" >/dev/null \
		&& [ "$BASH_STATUS" = "$MINI_STATUS" ]; then
		echo " OK"
		OK=$((OK + 1))
	else
		echo " NG"
		echo "  bash_status=$BASH_STATUS mini_status=$MINI_STATUS"
		echo "  diff:"
		diff -u "$BASH_OUT" "$MINI_OUT"
		if [ -s "$MINI_ERR" ]; then
			echo "  minishell stderr:"
			sed 's/^/    /' "$MINI_ERR"
		fi
		NG=$((NG + 1))
	fi
}

assert_case()
{
	name=$1
	input=$2
	cleanup_files
	run_bash "$input"
	run_mini "$input"
	print_result "$name"
}

summary()
{
	echo
	echo "========== summary =========="
	echo "total: $TOTAL"
	echo "ok   : $OK"
	echo "ng   : $NG"
	rm -rf "$TMP_DIR"
	if [ "$NG" -eq 0 ]; then
		exit 0
	fi
	exit 1
}

setup

echo "========== pipe =========="
assert_case "simple pipe" \
	"echo hello | cat\n"
assert_case "pipe to wc" \
	"echo hello | wc -c\n"
assert_case "multi pipe" \
	"echo hello | cat | wc -l\n"
assert_case "grep through pipe" \
	"echo hello | grep ll\n"
assert_case "pipe last status success" \
	"false | true\n"
assert_case "pipe last status failure" \
	"true | false\n"
assert_case "pipe with output redirect" \
	"echo hello | cat > out_pipe\ncat out_pipe\n"
assert_case "input redirect into pipe" \
	"echo apple > infile\ncat < infile | grep app\n"
assert_case "quote pipe character" \
	"echo 'a|b' | cat\n"

echo

echo "========== heredoc =========="
assert_case "simple heredoc" \
	"cat << EOF\nhello\nworld\nEOF\n"
assert_case "heredoc exact delimiter" \
	"cat << EOF\nEOFx\nEOF\n"
assert_case "heredoc to wc" \
	"cat << EOF | wc -l\none\ntwo\nEOF\n"
assert_case "heredoc to grep" \
	"cat << EOF | grep two\none\ntwo\nEOF\n"
assert_case "heredoc output redirect" \
	"cat << EOF > out_heredoc\nhello\nEOF\ncat out_heredoc\n"
assert_case "heredoc pipe redirect mix" \
	"cat << EOF | grep ll > out_mix\nhello\nworld\nEOF\ncat out_mix\n"

summary
