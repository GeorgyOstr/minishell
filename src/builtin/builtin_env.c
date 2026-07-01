/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 22:13:13 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 13:25:02 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include <unistd.h>

static int	err_env(void);
int			exec_env(char **argv, t_shell *shell);

static int	err_env(void)
{
	write(2, "env: too many arguments\n", 24);
	return (1);
}

int	exec_env(char **argv, t_shell *shell)
{
	char	**env;

	if (argv[1])
		return (err_env());
	env = shell->envp;
	while (*env)
	{
		if (ft_strchr(*env, '=') != NULL)
		{
			write(1, *env, ft_strlen(*env));
			write(1, "\n", 1);
		}
		env++;
	}
	return (0);
}
