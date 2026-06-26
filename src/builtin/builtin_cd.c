/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 23:20:22 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/27 00:07:17 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include <unistd.h>.
#include <limits.h>

char	*get_env_value(char **envp, char *str);
int		exec_cd(char **argv, t_shell *shell);

char	*get_env_value(char **envp, char *str)
{
	size_t	len;

	if (!envp || !str)
		return (NULL);
	len = ft_strlen(str);
	while (*envp)
	{
		if (ft_strncmp(*envp, str, len) == 0
			&& (*envp)[len] == '=')
			return (&(*envp)[len + 1]);
		envp++;
	}
	return (NULL);   
}

int	exec_cd(char **argv, t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (!argv[1])
		return (0);
	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	oldpwd = get_env_value(shell->envp, "PWD");
	if (chdir(argv[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	if (oldpwd)
		set_env(shell, "OLDPWD", oldpwd);
	if (getcwd(cwd, PATH_MAX))
		set_env(shell, "PWD", cwd);
	return (0);
}
