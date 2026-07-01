/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 21:09:00 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 13:32:09 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "token.h"
#include <stdlib.h>

static int		is_redir(t_token_type type);
static t_ast	*make_redir_node(t_token *op, t_token *file);
static void		append_redir(t_ast **tree, t_ast *cmd, t_ast *redir);
static int		handle_redir(t_token **tokens, int *pos, t_ast **tree,
					t_ast *cmd);
t_ast			*parse_command(t_token *tokens, int start, int end);

static int	is_redir(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_APPEND
		|| type == T_HEREDOC);
}

static void	append_redir(t_ast **tree, t_ast *cmd, t_ast *redir)
{
	t_ast	*cur;

	if (*tree == cmd)
	{
		redir->left = cmd;
		*tree = redir;
		return ;
	}
	cur = *tree;
	while (cur->left != cmd)
		cur = cur->left;
	redir->left = cmd;
	cur->left = redir;
}

static t_ast	*make_redir_node(t_token *op, t_token *file)
{
	t_ast	*redir;

	redir = new_node(NODE_REDIR);
	if (!redir)
		return (NULL);
	redir->redir_type = op->type;
	redir->file = ft_strdup(file->value);
	if (!redir->file)
	{
		free_ast(redir);
		return (NULL);
	}
	return (redir);
}

static int	handle_redir(t_token **tokens, int *pos, t_ast **tree, t_ast *cmd)
{
	t_ast	*redir;

	if (!(*tokens)->next || (*tokens)->next->type != T_WORD)
		return (1);
	redir = make_redir_node(*tokens, (*tokens)->next);
	if (!redir)
		return (1);
	append_redir(tree, cmd, redir);
	*tokens = (*tokens)->next;
	(*pos)++;
	return (0);
}

t_ast	*parse_command(t_token *tokens, int start, int end)
{
	t_ast	*cmd;
	t_ast	*tree;
	int		pos;

	cmd = new_node(NODE_CMD);
	if (!cmd)
		return (NULL);
	tree = cmd;
	pos = 0;
	while (tokens && pos <= end)
	{
		if (pos >= start && tokens->type == T_WORD)
		{
			if (add_word(cmd, tokens->value) != 0)
				return (free_ast(tree), NULL);
		}
		else if (pos >= start && is_redir(tokens->type))
		{
			if (handle_redir(&tokens, &pos, &tree, cmd) != 0)
				return (free_ast(tree), NULL);
		}
		tokens = tokens->next;
		pos++;
	}
	return (tree);
}
