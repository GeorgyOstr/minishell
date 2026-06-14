/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:51:51 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 13:32:06 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	result;

	result = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		result++;
	}
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list node_arr[10];
// 	t_list *head = &node_arr[0];
// 	char *nums[] = {"zero", "one", "two", "three", "four",
// 		"five", "six", "seven", "eight", "nine"};

// 	int i = 0;

// 	while (i < 10)
// 	{
// 		node_arr[i].content = nums[i];
// 		node_arr[i].next = (i < 9) ? &node_arr[i + 1] : NULL;
// 		i++;
// 	}
//     printf("%d\n", ft_lstsize(head));

// 	return (0);
// }