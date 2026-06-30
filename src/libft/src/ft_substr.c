/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:57:10 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/06 11:37:07 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

// #include <stdio.h>

// int main()
// {
// 	const char *s = "01233456789";
// 	unsigned int  start = 4;

// 	size_t len = 8;

// 	char *result = ft_substr(s, start, len);
// 	printf("%s", result);
// 	free(result);

// 	// start >= strlen(s)
// 	char *r1 = ft_substr("test", 10, 5);  // → ""
// 	printf("[%s]\n", r1);
// 	free(r1);

// 	// len == 0
// 	char *r2 = ft_substr("test", 2, 0);  // → ""
// 	printf("[%s]\n", r2);
// 	free(r2);

// 	return (0);
// }