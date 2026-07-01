/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:55:02 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 12:11:38 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:55:02 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 12:01:30 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	write_line_to_pipe(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) < 0)
		return (1);
	if (write(fd, "\n", 1) < 0)
		return (1);
	return (0);
}

static int	read_heredoc_lines(t_ast *node, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (ft_strncmp(line, node->file, ft_strlen(node->file) + 1) == 0)
		{
			free(line);
			return (0);
		}
		if (write_line_to_pipe(write_fd, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
}

static void	heredoc_child(t_ast *node, int pipefd[2])
{
	setup_signals_child();
	close(pipefd[0]);
	if (read_heredoc_lines(node, pipefd[1]))
	{
		close(pipefd[1]);
		exit(1);
	}
	close(pipefd[1]);
	exit(0);
}

static int	run_heredoc_input(t_ast *node, int pipefd[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		close(pipefd[1]);
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		heredoc_child(node, pipefd);
	close(pipefd[1]);
	setup_signals_exec();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (130);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (1);
	return (0);
}

int	open_heredoc_fd(t_ast *node, int *read_fd)
{
	int	pipefd[2];
	int	rc;

	if (pipe(pipefd) < 0)
		return (1);
	rc = run_heredoc_input(node, pipefd);
	if (rc != 0)
	{
		close(pipefd[0]);
		return (rc);
	}
	*read_fd = pipefd[0];
	return (0);
}

// #include "command.h"
// #include "libft.h"
// #include "shell.h"
// #include <signal.h>
// #include <stdio.h>
// #include <readline/readline.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int	open_heredoc_fd(t_ast *node, int *read_fd)
// {
// 	int	pipefd[2];
// 	int	rc;

// 	if (pipe(pipefd) < 0)
// 		return (1);
// 	rc = run_heredoc_input(node, pipefd);
// 	if (rc != 0)
// 	{
// 		close(pipefd[0]);
// 		return (rc);
// 	}
// 	*read_fd = pipefd[0];
// 	return (0);
// }

// static int	write_line_to_pipe(int fd, char *line)
// {
// 	if (write(fd, line, ft_strlen(line)) < 0)
// 		return (1);
// 	if (write(fd, "\n", 1) < 0)
// 		return (1);
// 	return (0);
// }

// static int	read_heredoc_lines(t_ast *node, int write_fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			return (0);
// 		if (ft_strncmp(line, node->file, ft_strlen(node->file) + 1) == 0)
// 		{
// 			free(line);
// 			return (0);
// 		}
// 		if (write_line_to_pipe(write_fd, line))
// 		{
// 			free(line);
// 			return (1);
// 		}
// 		free(line);
// 	}
// }
// static int	set_heredoc_stdin(int read_fd, int *backup)
// {
// 	*backup = dup(STDIN_FILENO);
// 	if (*backup < 0)
// 		return (1);
// 	if (dup2(read_fd, STDIN_FILENO) < 0)
// 	{
// 		close(*backup);
// 		return (1);
// 	}
// 	close(read_fd);
// 	return (0);
// }

// static int	restore_stdin(int backup)
// {
// 	if (dup2(backup, STDIN_FILENO) < 0)
// 	{
// 		close(backup);
// 		return (1);
// 	}
// 	close(backup);
// 	return (0);
// }

// /*
// ** Heredoc reader child. Uses default signals so Ctrl+C terminates it,
// ** which lets the parent know the heredoc was cancelled.
// */
// static void	heredoc_child(t_ast *node, int pipefd[2])
// {
// 	setup_signals_child();
// 	close(pipefd[0]);
// 	if (read_heredoc_lines(node, pipefd[1]))
// 	{
// 		close(pipefd[1]);
// 		exit(1);
// 	}
// 	close(pipefd[1]);
// 	exit(0);
// }

// /*
// ** Fork the heredoc reader. Returns 0 on success, 130 if cancelled with
// ** Ctrl+C, and 1 on any other error.
// */
// static int	run_heredoc_input(t_ast *node, int pipefd[2])
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid < 0)
// 		return (close(pipefd[1]), perror("minishell: fork"), 1);
// 	if (pid == 0)
// 		heredoc_child(node, pipefd);
// 	close(pipefd[1]);
// 	setup_signals_exec();
// 	waitpid(pid, &status, 0);
// 	setup_signals_interactive();
// 	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		return (130);
// 	}
// 	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
// 		return (1);
// 	return (0);
// }

// int	exec_heredoc(t_shell *shell, t_ast *node)
// {
// 	int	pipefd[2];
// 	int	backup;
// 	int	status;
// 	int	rc;

// 	if (pipe(pipefd) < 0)
// 		return (1);
// 	rc = run_heredoc_input(node, pipefd);
// 	if (rc != 0)
// 	{
// 		close(pipefd[0]);
// 		return (rc);
// 	}
// 	if (set_heredoc_stdin(pipefd[0], &backup))
// 	{
// 		close(pipefd[0]);
// 		return (1);
// 	}
// 	status = exec_ast(shell, node->left);
// 	if (restore_stdin(backup))
// 		return (1);
// 	return (status);
// }
