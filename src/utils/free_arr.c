/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 19:39:08 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/14 20:04:59 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

char **free_arr(char **arr)
{
    size_t i;

    i = 0;

    if (!arr)
        return (NULL);
    while(arr[i])
        free(arr[i++]);
    free(arr);
    return (NULL);
}
