*This project has been created as part of the 42 curriculum by hisasano, gostroum.*

# Minishell

## Description

Minishell is a small Unix shell written in C.

The goal of this project is to recreate a simplified version of Bash and to learn how a shell works internally. Through this project, we learned how to manage processes, file descriptors, pipes, redirections, signals, environment variables, and command parsing.

The shell displays an interactive prompt, reads user input, tokenizes and parses the command line, expands environment variables, and executes built-in or external commands.

### Features

- Interactive prompt using `readline`
- Command history
- Execution of external commands
- Search for executables using the `PATH` environment variable
- Execution using relative or absolute paths
- Built-in commands:
  - `echo` with option `-n`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Redirections:
  - `<` input redirection
  - `>` output redirection
  - `>>` output redirection in append mode
  - `<<` heredoc
- Pipes using `|`
- Quote handling:
  - Single quotes prevent interpretation of metacharacters
  - Double quotes prevent interpretation of metacharacters except `$`
- Environment variable expansion:
  - `$VAR`
  - `$?`
- Exit status management
- Signal handling for:
  - `Ctrl-C`
  - `Ctrl-D`
  - `Ctrl-\`

### Project Structure

```text
.
├── include/        Header files
├── src/
│   ├── main/       Shell initialization, readline loop, signal setup
│   ├── lexer/      Tokenization of user input
│   ├── parser/     AST construction
│   ├── expander/   Environment variable expansion
│   ├── execve/     Command execution, pipes, redirections, heredoc
│   ├── builtin/    Built-in command implementations
│   ├── utils/      Utility functions
│   └── libft/      Personal libft library
└── Makefile
```

## Instructions

### Requirements

- C compiler (`cc`)
- `make`
- `readline` library

On macOS, this Makefile uses Homebrew readline when building on Darwin.

### Build

```bash
make
```

### Run

```bash
./minishell
```

Example:

```bash
minishell$ echo hello
hello
minishell$ echo $HOME
/Users/username
minishell$ ls | grep .c > files.txt
minishell$ cat << EOF
> hello
> EOF
hello
```

### Clean

```bash
make clean
```

### Full clean

```bash
make fclean
```

### Rebuild

```bash
make re
```

## Testing

The following tests can be executed manually after building the project.

Build:

```bash
make
./minishell
```

### Basic commands

```bash
echo hello
pwd
ls
/bin/ls
```

### Built-in commands

```bash
echo hello
echo -n hello
pwd
cd ..
pwd
export TEST_VAR=hello
env
unset TEST_VAR
env
exit
```

### Environment variable expansion

```bash
echo $HOME
echo "$HOME"
echo '$HOME'
echo $NO_SUCH_VAR
echo "$NO_SUCH_VAR"
echo abc$USER
echo "$USER.txt"
```

### Exit status

```bash
true
echo $?
false
echo $?
nosuchcommand
echo $?
```

### Quotes

```bash
echo 'hello world'
echo "hello world"
echo '$HOME'
echo "$HOME"
echo 'a | b'
echo "a > b"
```

### Redirections

```bash
echo hello > out.txt
cat out.txt
echo world >> out.txt
cat out.txt
cat < out.txt
rm out.txt
```

### Pipes

```bash
echo hello | cat
echo hello | wc -c
ls | grep Makefile
cat /etc/passwd | grep root | wc -l
```

### Heredoc

```bash
cat << EOF
hello
world
EOF
```

```bash
cat << EOF | grep hello
hello
world
EOF
```

### Signal behavior

Run `./minishell` in interactive mode and check:

```text
Ctrl-C  -> displays a new prompt on a new line
Ctrl-D  -> exits minishell
Ctrl-\  -> does nothing in interactive mode
```

### Memory and file descriptor checks

When available, Valgrind can be used to check for leaks:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

The `readline()` function may report internal leaks. The important point is that memory allocated by the project itself is properly freed.


## Notes

This project intentionally implements only the behavior required by the 42 subject. Features that are not required, such as `;`, `\`, command substitution, job control, or advanced Bash grammar, are outside the scope of this implementation.

When behavior is ambiguous, Bash was used as the reference.

## Resources

- 42 School Minishell subject PDF
- GNU Bash manual
- Linux man pages / POSIX documentation:
  - `readline`
  - `fork`
  - `execve`
  - `waitpid`
  - `access`
  - `open`
  - `dup`
  - `dup2`
  - `pipe`
  - `signal`
  - `sigaction`
  - `getcwd`
  - `chdir`
  - etc.
- The 42 Norm
- Peer review and debugging discussions

### AI Usage

AI was used as a learning and debugging assistant during the project.

Main use cases included:


- Reviewing parser and AST design ideas
- Reviewing signal-handling behavior for `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`
- Creating and improving local test cases
- Improving README structure and technical explanations

AI was not used to blindly generate or copy complete project logic.
All code was written, tested, debugged, and fully understood by myself.
