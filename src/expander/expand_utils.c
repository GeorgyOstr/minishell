/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:18:13 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/30 22:27:41 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include <stdlib.h>

int	is_env_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*append_expanded_str(char *left, char *right)
{
	char	*joined;

	if (!left || !right)
	{
		free(left);
		return (NULL);
	}
	joined = ft_strjoin(left, right);
	free(left);
	return (joined);
}

char	*append_expanded_char(char *str, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (append_expanded_str(str, buf));
}
