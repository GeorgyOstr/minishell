/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:12:17 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 13:25:31 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "shell.h"
#include <stdio.h>
#include <unistd.h>

void	split_key_val(char *env, char **key, char **val)
{
	*key = env;
	*val = ft_strchr(env, '=');
	if (*val != NULL)
	{
		**val = '\0';
		(*val)++;
	}
}

int	is_valid_key(char *key)
{
	int	i;

	if (!key)
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	print_error_export(char *key, char *val)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	if (val)
	{
		ft_putchar_fd('=', 2);
		ft_putstr_fd(val, 2);
	}
	ft_putendl_fd("': not a valid identifier", 2);
}

int	exec_export(char **argv, t_shell *shell)
{
	char	*key;
	char	*val;
	int		status;

	argv++;
	if (!*argv)
		return (print_export(shell->envp));
	status = 0;
	while (*argv)
	{
		split_key_val(*argv, &key, &val);
		if (!is_valid_key(key))
		{
			print_error_export(key, val);
			status = 1;
		}
		else if (set_env_var(shell, key, val) != 0)
			return (1);
		argv++;
	}
	return (status);
}
