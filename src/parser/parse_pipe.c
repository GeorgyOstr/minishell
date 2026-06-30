/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:50:09 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/23 18:17:46 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "token.h"
#include "utils.h"
#include <stdlib.h>

static int	find_end_pipe(t_token *tokens, int start, int end);
t_ast		*new_node(t_node_type type);
void		free_ast(t_ast *node);
t_ast		*parse_pipe(t_token *tokens, int start, int end);

static int	find_end_pipe(t_token *tokens, int start, int end)
{
	int		pos;
	int		last_pipe;
	t_token	*head;

	pos = 0;
	last_pipe = -1;
	head = tokens;
	while (head && pos <= end)
	{
		if (pos >= start && head->type == T_PIPE)
			last_pipe = pos;
		head = head->next;
		pos++;
	}
	return (last_pipe);
}

t_ast	*new_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->argv = NULL;
	node->redir_type = 0;
	node->file = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	free_arr(node->argv);
	free(node->file);
	free(node);
}

t_ast	*parse_pipe(t_token *tokens, int start, int end)
{
	t_ast	*node;
	int		pipe_pos;

	if (start > end)
		return (NULL);
	pipe_pos = find_end_pipe(tokens, start, end);
	if (pipe_pos == start || pipe_pos == end)
		return (NULL);
	if (pipe_pos != -1)
	{
		node = new_node(NODE_PIPE);
		if (!node)
			return (NULL);
		node->left = parse_pipe(tokens, start, pipe_pos - 1);
		node->right = parse_pipe(tokens, pipe_pos + 1, end);
		if (!node->left || !node->right)
		{
			free_ast(node);
			return (NULL);
		}
		return (node);
	}
	return (parse_command(tokens, start, end));
}
