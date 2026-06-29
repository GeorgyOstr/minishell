/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:36:00 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/29 20:39:10 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	open_redir_file(t_ast *node)
{
	if (node->redir_type == T_REDIR_IN)
		return (open(node->file, O_RDONLY));
	if (node->redir_type == T_REDIR_OUT)
		return (open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (node->redir_type == T_APPEND)
		return (open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	get_target_fd(t_ast *node)
{
	if (node->redir_type == T_REDIR_IN)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int	exec_redir(t_shell *shell, t_ast *node)
{
	int	fd;
	int	backup;
	int	target;
	int	status;

	if (node->redir_type == T_HEREDOC)
		return (exec_heredoc(shell, node));
	fd = open_redir_file(node);
	if (fd < 0)
	{
		perror(node->file);
		return (1);
	}
	target = get_target_fd(node);
	backup = dup(target);
	if (backup < 0)
		return (close(fd), 1);
	if (dup2(fd, target) < 0)
		return (close(fd), close(backup), 1);
	close(fd);
	status = exec_ast(shell, node->left);
	dup2(backup, target);
	close(backup);
	return (status);
}
