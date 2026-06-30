/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:55:02 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/29 20:43:28 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "shell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
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
static int	set_heredoc_stdin(int read_fd, int *backup)
{
	*backup = dup(STDIN_FILENO);
	if (*backup < 0)
		return (1);
	if (dup2(read_fd, STDIN_FILENO) < 0)
	{
		close(*backup);
		return (1);
	}
	close(read_fd);
	return (0);
}

static int	restore_stdin(int backup)
{
	if (dup2(backup, STDIN_FILENO) < 0)
	{
		close(backup);
		return (1);
	}
	close(backup);
	return (0);
}

int	exec_heredoc(t_shell *shell, t_ast *node)
{
	int	pipefd[2];
	int	backup;
	int	status;

	if (pipe(pipefd) < 0)
		return (1);
	if (read_heredoc_lines(node, pipefd[1]))
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	close(pipefd[1]);
	if (set_heredoc_stdin(pipefd[0], &backup))
	{
		close(pipefd[0]);
		return (1);
	}
	status = exec_ast(shell, node->left);
	if (restore_stdin(backup))
		return (1);
	return (status);
}
