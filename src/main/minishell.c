/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:08:42 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/14 20:55:34 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "libft.h"
#include "utils.h"

static void	ms_init_env(t_shell *shell, char **envp);
static char	**dup_envp(char **arr);

int minishell(char **envp)
{
    t_shell shell;

    ms_init_env(&shell, envp);
    read_line_loop(&shell);

    free_arr(shell.envp);
    return (shell.last_status);
}

static void	ms_init_env(t_shell *shell, char **envp)
{
	shell->last_status = 0;
	shell->should_exit = 0;
	shell->envp = dup_envp(envp);
	if (!shell->envp)
		perror("minishell");
	return ;
}

static char **dup_envp(char **arr)
{
    char **result;
    size_t i;
    size_t ar_count;

    i = 0;
    ar_count = 0;

    if (!arr)
        return (NULL);

    while(arr[i])
        i++;

    result = ft_calloc(i + 1, sizeof(char *));
    if (!result)
        return (NULL);
    while(arr[ar_count])
    {
        result[ar_count] = ft_strdup(arr[ar_count]);
        if (!result[ar_count])
            return (free_arr(result));
        ar_count++;
    }
    return(result);
}
