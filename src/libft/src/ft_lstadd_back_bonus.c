/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:21:14 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 13:23:29 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end = *lst;
	while (end->next != NULL)
		end = end->next;
	end->next = new;
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
// 	newnode->content = "ten";
// 	newnode->next = NULL;

// 	int i = 0;

// 	while (i < 10)
// 	{
// 		node_arr[i].content = nums[i];
// 		node_arr[i].next = (i < 9) ? &node_arr[i + 1] : NULL;
// 		i++;
// 	}
// 	ft_lstadd_back(&head, newnode);

// 	t_list *tmp = head;

// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	free(newnode);

// 	return (0);
// }