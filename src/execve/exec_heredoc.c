/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:55:02 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 14:36:10 by gostroum         ###   ########.fr       */
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
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
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
