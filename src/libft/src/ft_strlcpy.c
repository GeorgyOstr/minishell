/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:34:16 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 19:08:18 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	if (dstsize == 0)
		return (i);
	while (j < dstsize - 1 && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (i);
}

// #include <stdio.h>

// int main()
// {
//     size_t i = 5;
//     char src[] = "12345\0";
//     char dst[i];

//     size_t j = ft_strlcpy(dst, src, i);

//     printf("%zu", j);

//     return (0);
// }