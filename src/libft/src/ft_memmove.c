/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:32:55 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:36 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (s == d || len == 0)
		return (dst);
	if (d < s)
	{
		ft_memcpy(d, s, len);
	}
	else
	{
		i = len;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int main() {
//     char str[] = "0123456789";
//     char str_2[] = "0123456789";

//     printf("Before_ft : %s\n", str);
//     printf("Before : %s\n", str_2);
//     ft_memmove(str + 6, str, 5);
//     memmove(str_2 + 6, str_2, 5);
//     printf("After_ft :  %s\n", str);
//     printf("After :  %s\n", str_2);

//     return (0);
// }