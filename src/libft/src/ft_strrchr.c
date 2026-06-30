/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:35:12 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 19:08:44 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			result = (char *)&s[i];
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (result);
}

// #include <stdio.h>

// int main()
// {
//     const char s[] = "1234a678a9";
//     int c = 'a' + 256;

//     printf("%c : %s\n", c, ft_strrchr(s, c));
//     printf("%c : %s\n", c, strrchr(s, c));
//     return (0);
// }