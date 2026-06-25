/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 22:04:20 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/25 19:58:51 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

static char	*join_cmd_path(char *dir, char *cmd);
static char	*check_direct_path(char *cmd);
static char	*search_paths(char **paths, char *cmd);
char		*find_cmd_path(char *cmd, char **envp);

static char	*join_cmd_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

static char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (NULL);
		return (ft_strdup(cmd));
	}
	return (NULL);
}

static char	*search_paths(char **paths, char *cmd)
{
	char	*res;
	int		i;

	i = 0;
	while (paths[i])
	{
		res = join_cmd_path(paths[i], cmd);
		if (!res)
			return (NULL);
		if (access(res, X_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	*path_env;
	char	**paths;

	path = check_direct_path(cmd);
	if (path)
		return (path);
	path_env = get_env_value(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	path = search_paths(paths, cmd);
	free_arr(paths);
	return (path);
}
