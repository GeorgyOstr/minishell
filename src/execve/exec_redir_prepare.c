/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_prepare.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:16:39 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 12:16:57 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void	replace_fd(int *old_fd, int new_fd)
{
	if (*old_fd >= 0)
		close(*old_fd);
	*old_fd = new_fd;
}

static int	open_redir_file(t_ast *node)
{
	int	flags;

	if (node->redir_type == T_REDIR_IN)
		return (open(node->file, O_RDONLY));
	flags = O_WRONLY | O_CREAT;
	if (node->redir_type == T_REDIR_OUT)
		flags = flags | O_TRUNC;
	else if (node->redir_type == T_APPEND)
		flags = flags | O_APPEND;
	else
		return (-1);
	return (open(node->file, flags, 0644));
}

static int	prepare_heredoc_redir(t_ast *node, int *in_fd)
{
	int	fd;
	int	status;

	status = open_heredoc_fd(node, &fd);
	if (status != 0)
		return (status);
	replace_fd(in_fd, fd);
	return (0);
}

int	prepare_one_redir(t_ast *node, int *in_fd, int *out_fd)
{
	int	fd;

	if (node->redir_type == T_HEREDOC)
		return (prepare_heredoc_redir(node, in_fd));
	fd = open_redir_file(node);
	if (fd < 0)
	{
		perror(node->file);
		return (1);
	}
	if (node->redir_type == T_REDIR_IN)
		replace_fd(in_fd, fd);
	else
		replace_fd(out_fd, fd);
	return (0);
}
