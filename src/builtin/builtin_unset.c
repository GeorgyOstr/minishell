/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 19:10:00 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 13:55:34 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include <stdlib.h>

static int	is_same_env_key(char *env, char *key);
int			exec_unset(char **argv, t_shell *shell);
int			remove_env_var(t_shell *shell, char *key);
int			find_env_index(char **envp, char *key);
void		shift_env(char **envp, int index);

static int	is_same_env_key(char *env, char *key)
{
	int	len;

	len = ft_strlen(key);
	if (ft_strncmp(env, key, len) == 0 && env[len] == '=')
		return (1);
	return (0);
}

int	find_env_index(char **envp, char *key)
{
	int	i;

	if (!envp || !key)
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (is_same_env_key(envp[i], key))
			return (i);
		i++;
	}
	return (-1);
}

void	shift_env(char **envp, int index)
{
	int	i;

	i = index;
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
}

int	remove_env_var(t_shell *shell, char *key)
{
	int	index;

	if (!shell || !shell->envp || !key)
		return (0);
	index = find_env_index(shell->envp, key);
	if (index == -1)
		return (0);
	free(shell->envp[index]);
	shift_env(shell->envp, index);
	return (0);
}

int	exec_unset(char **argv, t_shell *shell)
{
	if (!argv)
		return (1);
	argv++;
	while (*argv)
	{
		remove_env_var(shell, *argv);
		argv++;
	}
	return (0);
}
