/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 18:12:42 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 13:32:06 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include <stdlib.h>

static int	argv_len(char **argv);
int			add_word(t_ast *node, char *value);

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

int	add_word(t_ast *node, char *value)
{
	char	**new_argv;
	int		len;
	int		i;

	len = argv_len(node->argv);
	new_argv = malloc(sizeof(char *) * (len + 2));
	if (!new_argv)
		return (1);
	i = 0;
	while (i < len)
	{
		new_argv[i] = node->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(value);
	if (!new_argv[i])
	{
		free(new_argv);
		return (1);
	}
	new_argv[i + 1] = NULL;
	free(node->argv);
	node->argv = new_argv;
	return (0);
}
