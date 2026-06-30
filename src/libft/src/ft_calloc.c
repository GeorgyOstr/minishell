/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:28:16 by hisasano          #+#    #+#             */
/*   Updated: 2025/05/06 14:44:53 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	void	*ptr;

	if (count == 0 || size == 0)
		return (malloc(0));
	else if (size > SIZE_MAX / count)
		return (NULL);
	bytes = count * size;
	ptr = malloc(bytes);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, bytes);
	return (ptr);
}

// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	size_t	count;
// 	size_t	size;
// 	void	*ptr_1;
// 	void	*ptr;

// 	count = SIZE_MAX / 2 + 1;
// 	size = 2;
// 	ptr_1 = ft_calloc(count, size);
// 	ptr = calloc(count, size);
// 	if (!ptr)
// 		puts("✅ calloc returned NULL (overflow detected)");
// 	else
// 		puts("⚠️ calloc succeeded (unexpected)");
// 	if (!ptr_1)
// 		puts("✅ ft_calloc returned NULL (overflow detected)");
// 	else
// 		puts("⚠️ ft_calloc succeeded (unexpected)");
// 	return (0);
// }

/* SIZE_MAX = 18446744073709551615 */