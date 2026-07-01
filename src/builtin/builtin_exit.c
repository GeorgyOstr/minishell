/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 23:16:07 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 12:37:27 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "shell.h"

static int	is_numeric_arg(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

static void	print_exit_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

int	exec_exit(char **argv, t_shell *shell)
{
	int	argc;

	argc = count_args(argv);
	if (argc == 1)
	{
		shell->should_exit = 1;
		return (shell->last_status);
	}
	if (!is_numeric_arg(argv[1]))
	{
		print_exit_error(argv[1], "numeric argument required");
		shell->should_exit = 1;
		shell->last_status = 255;
		return (255);
	}
	if (argc > 2)
	{
		print_exit_error(NULL, "too many arguments");
		shell->last_status = 1;
		return (1);
	}
	shell->should_exit = 1;
	shell->last_status = ft_atoi(argv[1]);
	return (shell->last_status);
}
