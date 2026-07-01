/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:56:01 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 14:15:18 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_only_space(char *line);
void		read_line_loop(t_shell *shell);
static void	handle_line(t_shell *shell, char *line);

static int	is_only_space(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

void	handle_line(t_shell *shell, char *line)
{
	if (line[0] != '\0')
		add_history(line);
	if (is_only_space(line))
		return ;
	if (make_cmd(shell, line))
		return ;
	shell->last_status = exec_ast(shell, shell->node);
	free_ast(shell->node);
	shell->node = NULL;
}

void	read_line_loop(t_shell *shell)
{
	char	*line;
	char	*prompt;

	rl_outstream = stderr;
	while (!shell->should_exit)
	{
		setup_signals_interactive();
		prompt = "";
		if (isatty(STDIN_FILENO))
			prompt = "minishell$ ";
		line = readline(prompt);
		if (g_signal == SIGINT)
		{
			shell->last_status = 130;
			g_signal = 0;
		}
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		handle_line(shell, line);
		free(line);
	}
}
