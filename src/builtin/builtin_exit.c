/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 23:16:07 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/27 22:25:09 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "shell.h"

int	exec_exit(char **argv, t_shell *shell)
{
	shell->should_exit = 1;
	if (argv[1])
		shell->last_status = ft_atoi(argv[1]);
	else
		shell->last_status = 0;
	return (shell->last_status);
}
