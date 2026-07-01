/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 19:07:08 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 13:45:19 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include <stdlib.h>

static int	find_env_index(char **envp, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && (envp[i][len] == '='
			|| envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	*join_key_val(char *key, char *val)
{
	char	*tmp;
	char	*res;

	if (!val)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, val);
	free(tmp);
	return (res);
}

static int	add_env_var(t_shell *shell, char *new_env)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_envp[i] = new_env;
	new_envp[i + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}

int	set_env_var(t_shell *shell, char *key, char *val)
{
	char	*new_env;
	int		index;

	new_env = join_key_val(key, val);
	if (!new_env)
		return (1);
	index = find_env_index(shell->envp, key);
	if (index >= 0)
	{
		free(shell->envp[index]);
		shell->envp[index] = new_env;
		return (0);
	}
	return (add_env_var(shell, new_env));
}
