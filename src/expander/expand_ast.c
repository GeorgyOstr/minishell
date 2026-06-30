/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:14:57 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/30 22:31:16 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "expander.h"
#include <stdlib.h>

static int	replace_word(char **word, t_shell *shell)
{
	char	*expanded;

	expanded = expand_word(*word, shell);
	if (!expanded)
		return (1);
	free(*word);
	*word = expanded;
	return (0);
}

static int	expand_argv(char **argv, t_shell *shell)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		if (replace_word(&argv[i], shell) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	expand_ast(t_ast *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (expand_argv(node->argv, shell));
	if (node->type == NODE_REDIR && node->redir_type != T_HEREDOC)
		return (replace_word(&node->file, shell));
	return (0);
}
