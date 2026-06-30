/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 18:34:13 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/29 19:53:06 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	close_pipe_fd(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

static void	exec_left_child(t_shell *shell, t_ast *node, int pipefd[2])
{
	setup_signals_child();
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2");
		exit(1);
	}
	close_pipe_fd(pipefd);
	exit(exec_ast(shell, node->left));
}

static void	exec_right_child(t_shell *shell, t_ast *node, int pipefd[2])
{
	setup_signals_child();
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("minishell: dup2");
		exit(1);
	}
	close_pipe_fd(pipefd);
	exit(exec_ast(shell, node->right));
}

static int	wait_pipe(pid_t left_pid, pid_t right_pid)
{
	int	status;

	setup_signals_exec();
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	setup_signals_interactive();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		else if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_pipe(t_shell *shell, t_ast *node)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipefd) < 0)
		return (perror("minishell: pipe"), 1);
	left_pid = fork();
	if (left_pid < 0)
		return (close_pipe_fd(pipefd), perror("minishell: fork"), 1);
	if (left_pid == 0)
		exec_left_child(shell, node, pipefd);
	right_pid = fork();
	if (right_pid < 0)
		return (close_pipe_fd(pipefd), perror("minishell: fork"), 1);
	if (right_pid == 0)
		exec_right_child(shell, node, pipefd);
	close_pipe_fd(pipefd);
	return (wait_pipe(left_pid, right_pid));
}
