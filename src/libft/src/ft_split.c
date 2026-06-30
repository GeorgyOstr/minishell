/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:10:28 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/06 12:13:07 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_arr(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s != '\0')
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static char	*ft_get_word(const char *s, char c, int arrcount)
{
	int	i;
	int	start;
	int	end;
	int	word_count;

	i = 0;
	start = 0;
	end = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		end = i;
		if (word_count == arrcount)
			return (ft_substr(s, start, end - start));
		word_count++;
	}
	return (NULL);
}

static char	**free_all(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		arrcount;
	int		size;
	char	**result;

	arrcount = 0;
	if (s == NULL)
		return (NULL);
	size = ft_count_arr(s, c);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
	{
		return (NULL);
	}
	while (arrcount < size)
	{
		result[arrcount] = ft_get_word(s, c, arrcount);
		if (!result[arrcount])
			return (free_all(result, arrcount));
		arrcount++;
	}
	result[arrcount] = NULL;
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*s = "123,,,456,,,789";
// 	char		c;
// 	char		**result;
// 	int			i;

// 	c = ',';
// 	result = ft_split(s, c);
// 	i = 0;
// 	printf("%s, %c\n", s, c);
// 	while (result[i] != NULL)
// 	{
// 		printf("%s\n", result[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (result[i] != NULL)
// 	{
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// 	return (0);
// }
