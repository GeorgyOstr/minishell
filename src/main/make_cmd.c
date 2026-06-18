/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 22:41:33 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/17 19:43:11 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "command.h"
#include "token.h"
#include "minishell.h"

static void test_print_tokens(t_token *tokens);
int	make_cmd(t_shell *shell, char *line);

static void test_print_tokens(t_token *tokens)
{
    while(tokens)
    {
        printf("value=[%s] type=%d\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
}

int	make_cmd(t_shell *shell, char *line)
{
    t_token *tokens;

	(void)shell;

	tokens = NULL;
	if (lexer(&tokens, line) != 0)
		return (1);
	// if (parser(shell, tokens) != 0)
	// {
	// 	free_tokens(tokens);
	// 	return (1);
	// }
	test_print_tokens(tokens);
	free_tokens(tokens);
	return (0);
}
