/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:12:45 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 13:24:17 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	t_list node_arr[10];
// 	t_list *head = &node_arr[0];
// 	char *nums[] = {"zero", "one", "two", "three", "four",
// 		"five", "six", "seven", "eight", "nine"};

// 	t_list *newnode = (t_list *)malloc(sizeof(t_list));
// 	newnode->content = "minus";
// 	newnode->next = NULL;

// 	int i = 0;

// 	while (i < 10)
// 	{
// 		node_arr[i].content = nums[i];
// 		node_arr[i].next = (i < 9) ? &node_arr[i + 1] : NULL;
// 		i++;
// 	}
// 	ft_lstadd_front(&head, newnode);

// 	t_list *tmp = head;

// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	free(newnode);

// 	return (0);
// }