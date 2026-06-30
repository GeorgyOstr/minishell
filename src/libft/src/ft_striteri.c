/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:17:55 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/06 13:09:05 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void	test_print(unsigned int n, char *s)
// {
// 	printf("%d : %s\n", n, s);
// }

// int main()
// {
// 	char s[] = "123456789";
// 	ft_striteri(s, test_print);

// 	return (0);
// }
