/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 22:41:33 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/25 20:01:10 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "command.h"
#include "token.h"
#include "shell.h"

// static void test_print_tokens(t_token *tokens);
static int token_count(t_token *tokens);
int	make_cmd(t_shell *shell, char *line);

// static void test_print_tokens(t_token *tokens)
// {
//     while(tokens)
//     {
//         printf("value=[%s] type=%d\n", tokens->value, tokens->type);
//         tokens = tokens->next;
//     }
// }

// static void	print_indent(int depth)
// {
// 	while (depth--)
// 		printf("  ");
// }

// static void	test_print_ast(t_ast *node, int depth)
// {
// 	int	i;

// 	if (!node)
// 		return ;
// 	print_indent(depth);
// 	if (node->type == NODE_PIPE)
// 		printf("PIPE\n");
// 	else if (node->type == NODE_REDIR)
// 		printf("REDIR (%d)\n", node->redir_type);
// 	else if (node->type == NODE_CMD)
// 	{
// 		printf("CMD:");
// 		i = 0;
// 		while (node->argv && node->argv[i])
// 		{
// 			printf(" %s", node->argv[i]);
// 			i++;
// 		}
// 		printf("\n");
// 	}
// 	if (node->file)
// 	{
// 		print_indent(depth + 1);
// 		printf("FILE: %s\n", node->file);
// 	}
// 	test_print_ast(node->left, depth + 1);
// 	test_print_ast(node->right, depth + 1);
// }

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
	// test_print_tokens(tokens);
	// test_print_ast(shell->node, 0);
	return (0);
}
