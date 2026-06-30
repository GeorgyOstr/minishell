#!/bin/bash

make || exit 1

run()
{
	printf "%-30s : " "$1"
	echo "$1" | ./minishell > out 2> err
	status=$?
	echo "status=$status"
	cat err
}

run "ls"
run "ls -l"
run "/bin/ls"
run "aaaaaaaa"
run "./no_such_file"

touch no_exec.sh
chmod 644 no_exec.sh
run "./no_exec.sh"
rm -f no_exec.sh

env -i ./minishell << EOF > out_env 2> err_env
ls
EOF

echo "===== env -i result ====="
cat err_env
cat out_env

rm -f out err out_env err_env