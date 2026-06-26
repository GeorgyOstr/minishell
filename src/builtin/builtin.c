/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 20:18:33 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/25 20:22:25 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, char **argv)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (builtin_echo(argv));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(shell, argv));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (builtin_env(shell));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (builtin_export(shell, argv));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (builtin_unset(shell, argv));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (builtin_exit(shell, argv));
	return (1);
}
