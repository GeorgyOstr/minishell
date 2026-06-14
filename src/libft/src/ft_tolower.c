/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:35:42 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/05 13:59:20 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

// #include <stdio.h>

// int main()
// {
//     char c = 0;

//     while(c < 127)
//     {
//         printf(" %c > %c :", c, ft_tolower(c));
//         if(c % 5 == 0)
//             printf("\n");
//         c++;
//     }
//     return (0);
// }