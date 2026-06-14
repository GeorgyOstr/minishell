/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:06:49 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/06 14:12:11 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

// #include <stdio.h>

// int main()
// {
// 	t_list *node =  ft_lstnew("abcde");

// 	if (node)
// 	{
// 		printf("%s\n", (char *)(node->content));
// 		printf("%c\n", *(char *)((node->content) + 2));
// 		free(node);
// 	}

// 	int i = 12345;

// 	node = ft_lstnew(&i);

// 	if (node)
// 	{
// 		printf("%p\n", (int *)(node->content));
// 		printf("%d\n", *(int *)(node->content));
// 		free(node);
// 	}
// 	return (0);
// }