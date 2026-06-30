/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:32:39 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/06 14:18:18 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char src[] = "abcde";
// 	size_t i = 3;

// 	char dst[20];
// 	char dst_1[20];

// 	ft_memset(dst, 0, sizeof(dst));
// 	ft_memset(dst_1, 0, sizeof(dst_1));

// 	ft_memcpy(dst, src, i);
// 	memcpy(dst_1, src, i);

// 	dst[i] = '\0';
// 	dst_1[i] = '\0';

// 	printf("ft_memcpy: %s\n", dst);
// 	printf("memcpy   : %s\n", dst_1);

//     return (0);
// }