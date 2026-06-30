/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:25:17 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/22 16:44:21 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

// #include <stdio.h>

// void	del_content(void *content)
// {
// 	printf("free content: %s\n", (char *)content);
// 	free(content);
// }

// int	main(void)
// {
// 	const char *nums[] = {"zero", "one", "two", "three", "four",
// 		"five", "six", "seven", "eight", "nine"};

//     t_list *head = NULL;
//     t_list *tail = NULL;

// 	int i = 0;

// 	while (i < 10)
// 	{
//         t_list *new_node = malloc(sizeof(t_list));
//         if (!new_node)
//             return (1);
// 		new_node->content = ft_strdup(nums[i]);
// 		if (!new_node->content)
//         {
// 			free(new_node);
//             return (1);
//         }

// 		new_node->next = NULL;

//         if (!head)
//             head = new_node;
//         else
//             tail->next = new_node;
//         tail = new_node;
// 		i++;
// 	}

// 	t_list *cur = head;
//     while (cur)
// 	{
// 		printf("%s\n", (char *)cur->content);
// 		cur = cur->next;
// 	}

// 	ft_lstclear(&head, del_content);

// 	if (!head)
// 		printf("All nodes deleted\n");
// 	else
// 		printf("Error\n");

// 	return (0);
// 	return (0);
// }