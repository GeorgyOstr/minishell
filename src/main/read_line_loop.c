/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:56:01 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/25 19:54:09 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

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

	// (void)shell;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		handle_line(shell, line);
		free(line);
	}
	return ;
}
