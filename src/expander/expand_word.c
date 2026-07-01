/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:06:52 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/30 22:27:43 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	update_quote(char c, char *quote)
{
	if (is_quote(c) && *quote == 0)
	{
		*quote = c;
		return (1);
	}
	if (c == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

static char	*append_word_char(char *res, char c, int *i)
{
	res = append_expanded_char(res, c);
	*i += 1;
	return (res);
}

char	*expand_word(char *word, t_shell *shell)
{
	char	*res;
	int		i;
	char	quote;

	if (!word)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	quote = 0;
	while (word[i])
	{
		if (update_quote(word[i], &quote))
			i++;
		else if (word[i] == '$' && quote != '\'')
			res = expand_dollar(res, word, &i, shell);
		else
			res = append_word_char(res, word[i], &i);
		if (!res)
			return (NULL);
	}
	return (res);
}
