/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 23:20:22 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 13:23:44 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "shell.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

char	*get_env_value(char **envp, char *str);
int		exec_cd(char **argv, t_shell *shell);

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
		set_env_var(shell, "OLDPWD", oldpwd);
	if (getcwd(cwd, PATH_MAX))
		set_env_var(shell, "PWD", cwd);
	return (0);
}
