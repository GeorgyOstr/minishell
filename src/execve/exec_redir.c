/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:36:00 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 12:18:11 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "shell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void	close_redir_fds(int in_fd, int out_fd)
{
	if (in_fd >= 0)
		close(in_fd);
	if (out_fd >= 0)
		close(out_fd);
}

static int	run_redir_command(t_shell *shell, t_ast *cmd, int in_fd, int out_fd)
{
	int	backup[2];
	int	status;

	backup[0] = dup(STDIN_FILENO);
	if (backup[0] < 0)
		return (close_redir_fds(in_fd, out_fd), 1);
	backup[1] = dup(STDOUT_FILENO);
	if (backup[1] < 0)
		return (close(backup[0]), close_redir_fds(in_fd, out_fd), 1);
	if (in_fd >= 0 && dup2(in_fd, STDIN_FILENO) < 0)
		return (close_redir_fds(in_fd, out_fd), 1);
	if (out_fd >= 0 && dup2(out_fd, STDOUT_FILENO) < 0)
		return (close_redir_fds(in_fd, out_fd), 1);
	close_redir_fds(in_fd, out_fd);
	status = exec_ast(shell, cmd);
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
	return (status);
}

int	exec_redir(t_shell *shell, t_ast *node)
{
	int		in_fd;
	int		out_fd;
	int		status;
	t_ast	*cmd;

	in_fd = -1;
	out_fd = -1;
	cmd = node;
	while (cmd && cmd->type == NODE_REDIR)
	{
		status = prepare_one_redir(cmd, &in_fd, &out_fd);
		if (status != 0)
		{
			close_redir_fds(in_fd, out_fd);
			return (status);
		}
		cmd = cmd->left;
	}
	return (run_redir_command(shell, cmd, in_fd, out_fd));
}
