/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:00:58 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/27 23:17:39 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	**dup_env(char **envp);
static void	sort_env(char **envp);
static void	free_env_copy(char **envp);

static int	compare_env(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (ft_strncmp(s1, s2, len1));
	return (ft_strncmp(s1, s2, len2));
}

static char	**dup_env(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (free_env_copy(copy), NULL);
		i++;
	}
	return (copy);
}

static void	sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (compare_env(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	free_env_copy(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	print_export(char **envp)
{
	char	**copy;
	int		i;
	char	*eq;

	copy = dup_env(envp);
	if (!copy)
		return (1);
	sort_env(copy);
	i = 0;
	while (copy[i])
	{
		eq = ft_strchr(copy[i], '=');
		ft_putstr_fd("declare -x ", 1);
		if (eq)
		{
			write(1, copy[i], eq - copy[i] + 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(eq + 1, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd(copy[i], 1);
		i++;
	}
	return (free_env_copy(copy), 0);
}
