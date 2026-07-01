#!/usr/bin/env bash

MINISHELL=${MINISHELL:-./minishell}
BASH_REF=${BASH_REF:-/bin/bash}
TMP_DIR=".tmp_minishell_full_test"
FILTER_INPUT_ECHO=${FILTER_INPUT_ECHO:-1}

OK=0
NG=0

mkdir -p "$TMP_DIR"

normalize_common()
{
	sed \
		-e 's/\r$//' \
		-e 's/^minishell[$] //' \
		-e 's/^> //' \
		"$1"
}

normalize_with_input_filter()
{
	local src="$1"
	local input="$2"
	local tmp="$TMP_DIR/.norm_tmp"

	normalize_common "$src" > "$tmp"
	if [ "$FILTER_INPUT_ECHO" = "1" ]; then
		awk 'NR==FNR {seen[$0]=1; next} !($0 in seen)' "$input" "$tmp"
	else
		cat "$tmp"
	fi
}

run_case()
{
	local name="$1"
	local mode="$2"
	local input="$3"
	local in="$TMP_DIR/input"
	local bash_out="$TMP_DIR/bash.out"
	local bash_err="$TMP_DIR/bash.err"
	local mini_out="$TMP_DIR/mini.out"
	local mini_err="$TMP_DIR/mini.err"
	local bash_norm="$TMP_DIR/bash.norm"
	local mini_norm="$TMP_DIR/mini.norm"
	local bash_status
	local mini_status

	printf "%b" "$input" > "$in"

	"$BASH_REF" < "$in" > "$bash_out" 2> "$bash_err"
	bash_status=$?

	"$MINISHELL" < "$in" > "$mini_out" 2> "$mini_err"
	mini_status=$?

	if [ "$mode" = "full" ]; then
		cat "$bash_out" "$bash_err" > "$TMP_DIR/bash.all"
		cat "$mini_out" "$mini_err" > "$TMP_DIR/mini.all"
		normalize_common "$TMP_DIR/bash.all" > "$bash_norm"
		normalize_with_input_filter "$TMP_DIR/mini.all" "$in" > "$mini_norm"
	elif [ "$mode" = "stdout" ]; then
		normalize_common "$bash_out" > "$bash_norm"
		normalize_with_input_filter "$mini_out" "$in" > "$mini_norm"
	else
		: > "$bash_norm"
		: > "$mini_norm"
	fi

	if [ "$bash_status" = "$mini_status" ] && diff -u "$bash_norm" "$mini_norm" > "$TMP_DIR/diff"; then
		printf "%-55s OK\n" "$name"
		OK=$((OK + 1))
	else
		printf "%-55s NG\n" "$name"
		printf "  bash_status=%s mini_status=%s\n" "$bash_status" "$mini_status"
		if [ "$mode" != "status" ]; then
			printf "  diff:\n"
			cat "$TMP_DIR/diff"
		fi
		printf "  input:\n"
		sed 's/^/    /' "$in"
		NG=$((NG + 1))
	fi
}

cleanup_files()
{
	rm -f .tmp_msh_a .tmp_msh_b .tmp_msh_in .tmp_msh_out
	rm -f "$USER" 2> /dev/null
}

cleanup_files

echo "========== status =========="
run_case "status: true then echo \$?" full $'true\necho $?\n'
run_case "status: false then echo \$?" full $'false\necho $?\n'
run_case "status: false then exit" status $'false\nexit\n'
run_case "status: command not found" stdout $'nosuchcommand\necho $?\n'
run_case "status: empty quoted command" stdout $'""\necho $?\n'

echo
echo "========== basic command =========="
run_case "cmd: echo hello" full $'echo hello\n'
run_case "cmd: echo multiple args" full $'echo hello world 42\n'
run_case "cmd: /bin/echo absolute path" full $'/bin/echo abs\n'
run_case "cmd: pwd" full $'pwd\n'
run_case "cmd: empty line keeps status" full $'false\n\necho $?\n'

echo
echo "========== quotes =========="
run_case "quote: single quote keeps dollar" full $'echo \'$HOME\'\n'
run_case "quote: double quote expands dollar" full $'echo "$HOME"\n'
run_case "quote: pipe inside single quote" full $'echo \'a|b\'\n'
run_case "quote: redir inside double quote" full $'echo "a>b"\n'
run_case "quote: concat quoted strings" full $'echo \'abc\'"def"\n'
run_case "quote: mixed literal and quoted" full $'echo a"$USER"b\n'

echo
echo "========== expander =========="
run_case "expand: HOME" full $'echo $HOME\n'
run_case "expand: USER concat prefix" full $'echo abc$USER\n'
run_case "expand: USER concat suffix in double quote" full $'echo "$USER.txt"\n'
run_case "expand: unset variable" full $'echo $NO_SUCH_VAR\n'
run_case "expand: unset variable in double quote" full $'echo "$NO_SUCH_VAR"\n'
run_case "expand: single quote then double quote" full $'echo \'$USER\'"$HOME"\n'
run_case "expand: double quote then single quote" full $'echo "$USER"\'$HOME\'\n'
run_case "expand: multiple variables" full $'echo $USER$USER\n'

echo
echo "========== builtin =========="
run_case "builtin: echo -n" stdout $'echo -n hello\n'
run_case "builtin: echo -nnn" stdout $'echo -nnn hello\n'
run_case "builtin: export then echo" full $'export MSH_TEST=abc\necho $MSH_TEST\n'
run_case "builtin: unset then echo" full $'export MSH_TEST=abc\nunset MSH_TEST\necho $MSH_TEST\n'
run_case "builtin: env after export" stdout $'export MSH_TEST=abc\nenv | grep MSH_TEST\n'
run_case "builtin: cd relative" full $'mkdir -p .tmp_minishell_full_test/cd_dir\ncd .tmp_minishell_full_test/cd_dir\npwd\n'
run_case "builtin: cd too many args" stdout $'cd a b\necho $?\n'

echo
echo "========== redirection =========="
run_case "redir: output >" full $'echo hello > .tmp_msh_out\ncat .tmp_msh_out\nrm -f .tmp_msh_out\n'
run_case "redir: append >>" full $'echo one > .tmp_msh_out\necho two >> .tmp_msh_out\ncat .tmp_msh_out\nrm -f .tmp_msh_out\n'
run_case "redir: input <" full $'echo input > .tmp_msh_in\ncat < .tmp_msh_in\nrm -f .tmp_msh_in\n'
run_case "redir: multiple output redirs" full $'echo hello > .tmp_msh_a > .tmp_msh_b\ncat .tmp_msh_b\nrm -f .tmp_msh_a .tmp_msh_b\n'
run_case "redir: no spaces around redir" full $'echo hello>.tmp_msh_out\ncat .tmp_msh_out\nrm -f .tmp_msh_out\n'
run_case "redir: expand filename" full $'echo hello > $USER\ncat $USER\nrm -f $USER\n'
run_case "redir: missing input file" status $'cat < no_such_input_file\n'

echo
echo "========== pipe =========="
run_case "pipe: simple pipe" full $'echo hello | cat\n'
run_case "pipe: grep" full $'echo hello | grep h\n'
run_case "pipe: wc -l" full $'echo hello | wc -l\n'
run_case "pipe: multi pipe" full $'echo hello | cat | cat | wc -c\n'
run_case "pipe: last status success" full $'false | true\necho $?\n'
run_case "pipe: last status failure" full $'true | false\necho $?\n'
run_case "pipe: redir after pipe" full $'echo hello | cat > .tmp_msh_out\ncat .tmp_msh_out\nrm -f .tmp_msh_out\n'
run_case "pipe: redir before pipe" full $'echo hello > .tmp_msh_in\ncat < .tmp_msh_in | wc -c\nrm -f .tmp_msh_in\n'

echo
echo "========== heredoc =========="
run_case "heredoc: basic wc" full $'cat << EOF | wc -l\nhello\nworld\nEOF\n'
run_case "heredoc: grep through pipe" full $'cat << EOF | grep hello | wc -l\nhello\nbye\nEOF\n'
run_case "heredoc: no history requirement" full $'cat << EOF | wc -c\nabc\nEOF\n'
run_case "heredoc: multiple heredoc uses last one" full $'cat << A << B | wc -l\nignore\nA\none\ntwo\nB\n'

echo
echo "========== exit =========="
run_case "exit: no arg after false" status $'false\nexit\n'
run_case "exit: explicit 42" status $'exit 42\n'
run_case "exit: plus 42" status $'exit +42\n'
run_case "exit: minus 1" status $'exit -1\n'
run_case "exit: 256 wraps to 0" status $'exit 256\n'
run_case "exit: non numeric" status $'exit abc\n'
run_case "exit: too many args does not exit" stdout $'exit 1 2\necho $?\nexit\n'

cleanup_files

echo
echo "========== result =========="
echo "OK: $OK"
echo "NG: $NG"

if [ "$NG" -eq 0 ]; then
	exit 0
fi
exit 1
