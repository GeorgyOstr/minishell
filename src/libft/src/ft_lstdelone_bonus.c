/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 23:06:51 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 13:27:14 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// #include <stdio.h>

// void	del_content(void *content)
// {
// 	printf("free content: %s\n", (char *)content);
// 	free(content);
// }

// int	main(void)
// {
// 	t_list *node = malloc(sizeof(t_list));
// 	if (!node)
// 		return (1);

// 	char *str = ft_strdup("12345");
// 	if (!str)
// 	{
// 		free(node);
// 		return (1);
// 	}

// 	node->content = str;
// 	node->next = NULL;

// 	printf("before delete: %s\n", (char *)node->content);

// 	ft_lstdelone(node, del_content);

// 	printf("node deleted\n");

// 	return (0);
// }