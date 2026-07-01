/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:35:26 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/06 17:19:37 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_isset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	if (end == 0)
		return ((char *)ft_strdup(""));
	end--;
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	while (end >= start && ft_isset(s1[end], set))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
