/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:27:58 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/04 23:18:19 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

// int main() {
//     char buffer[10] = "abcdefghi";
//     size_t i = 3;

//     printf("Before : %s\n", buffer);
//     ft_bzero(buffer, i);
//     printf("After : %s\n", buffer + i);

//     return (0);
// }