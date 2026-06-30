/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 22:41:33 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/25 20:09:51 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "command.h"
#include "token.h"
#include "shell.h"

static int token_count(t_token *tokens);
int	make_cmd(t_shell *shell, char *line);

static int token_count(t_token *tokens)
{
	t_token *head;
	int i;

	head = tokens;
	i = 0; 
	while(head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	make_cmd(t_shell *shell, char *line)
{
    t_token *tokens;

	// (void)shell;

	tokens = NULL;
	if (lexer(&tokens, line) != 0)
		return (1);
	shell->node = parse_pipe(tokens, 0, token_count(tokens) - 1);
	free_tokens(tokens);
	if (!shell->node)
		return (1);
	return (0);
}
