/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:56:57 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 13:27:56 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>
// #include <stdlib.h>
// void	del_content(void *content)
// {
// 	free(content);
// }

// void	print_content(void *content)
// {
// 	printf("%s\n", (char *)content);
// }

// int	main(void)
// {
// 	const char *nums[] = {"zero", "one", "two", "three", "four",
// 		"five", "six", "seven", "eight", "nine"};

// 	t_list *head = NULL;
// 	t_list *tail = NULL;

// 	for (int i = 0; i < 10; i++)
// 	{
// 		t_list *new_node = malloc(sizeof(t_list));
// 		if (!new_node)
// 			return (1);
// 		new_node->content = strdup(nums[i]);
// 		if (!new_node->content)
// 		{
// 			free(new_node);
// 			return (1);
// 		}
// 		new_node->next = NULL;

// 		if (!head)
// 			head = new_node;
// 		else
// 			tail->next = new_node;
// 		tail = new_node;
// 	}

// 	ft_lstiter(head, print_content); 

// 	ft_lstclear(&head, del_content);
// 	if (!head)
// 		printf("All nodes deleted\n");
// 	else
// 		printf("Error\n");

// 	return (0);
// }