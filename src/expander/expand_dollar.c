/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:06:00 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/30 22:27:39 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include "shell.h"
#include "utils.h"
#include <stdlib.h>

static char	*expand_status(char *res, int *i, t_shell *shell)
{
	char	*status;

	status = ft_itoa(shell->last_status);
	if (!status)
	{
		free(res);
		return (NULL);
	}
	res = append_expanded_str(res, status);
	free(status);
	*i += 2;
	return (res);
}

static char	*expand_env(char *res, char *word, int *i, t_shell *shell)
{
	char	*key;
	char	*value;
	int		start;
	int		len;

	start = *i + 1;
	len = 0;
	while (is_env_name_char(word[start + len]))
		len++;
	key = ft_substr(word, start, len);
	if (!key)
	{
		free(res);
		return (NULL);
	}
	value = get_env_value(shell->envp, key);
	free(key);
	if (value)
		res = append_expanded_str(res, value);
	*i = start + len;
	return (res);
}

char	*expand_dollar(char *res, char *word, int *i, t_shell *shell)
{
	if (word[*i + 1] == '?')
		return (expand_status(res, i, shell));
	if (!is_env_name_char(word[*i + 1]))
	{
		res = append_expanded_char(res, '$');
		*i += 1;
		return (res);
	}
	return (expand_env(res, word, i, shell));
}
