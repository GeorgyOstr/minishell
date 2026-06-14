/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:31:42 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/06 14:15:00 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_myintlen(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		sign;
	int		len;
	char	*result;

	nb = n;
	sign = (n < 0);
	if (sign)
		nb = -nb;
	len = ft_myintlen(nb) + sign;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len-- > sign)
	{
		result[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign)
		result[0] = '-';
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int i = 2147483647;
// 	int j = -2147483648;
// int	k = 0;

// 	char *result_0;
// 	char *result_1;
// char *result_2;

// 	result_0 = ft_itoa(i);
// 	result_1 = ft_itoa(j);
// result_2 = ft_itoa(k);

// 	printf("%d : %s\n", i, result_0);
// 	printf("%d : %s\n", j, result_1);
// printf("%d : %s\n", k, result_2);

// 	free(result_0);
// 	free(result_1);
// free(result_2);

// 	return (0);
// }