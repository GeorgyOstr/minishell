/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:37:10 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/25 20:13:13 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "shell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	exec_child(t_shell *shell, t_ast *node);
int		exec_cmd(t_shell *shell, t_ast *node);
int		exec_ast(t_shell *shell, t_ast *node);

void	exec_child(t_shell *shell, t_ast *node)
{
	char	*path;
	int		err;

	path = find_cmd_path(node->argv[0], shell->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(node->argv[0], 2);
		exit(127);
	}
	execve(path, node->argv, shell->envp);
	err = errno;
	perror(path);
	free(path);
	if (err == EACCES)
		exit(126);
	exit(127);
}

int	exec_cmd(t_shell *shell, t_ast *node)
{
	pid_t	pid;
	int		status;

	if (!node || !node->argv || !node->argv[0])
		return (0);
	if (is_builtin(node->argv[0]))
		return (exec_builtin(shell, node->argv));
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		exec_child(shell, node);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_ast(t_shell *shell, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (exec_cmd(shell, node));
	return (1);
}
