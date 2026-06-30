/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:37:10 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/30 17:12:49 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "shell.h"
#include "builtin.h"
#include "expander.h"
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

	setup_signals_child();
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

static int	wait_child(pid_t pid)
{
	int	status;

	setup_signals_exec();
	waitpid(pid, &status, 0);
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

int	exec_cmd(t_shell *shell, t_ast *node)
{
	pid_t	pid;

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
	return (wait_child(pid));
}

int	exec_ast(t_shell *shell, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
	{
		if (expand_ast(node, shell) != 0)
			return (1);
		return (exec_cmd(shell, node));
	}
	if (node->type == NODE_REDIR)
	{
		if (expand_ast(node, shell) != 0)
			return (1);
		return (exec_redir(shell, node));
	}
	if (node->type == NODE_PIPE)
		return (exec_pipe(shell, node));
	return (1);
}
