/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 23:16:07 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/26 23:20:11 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtin.h"

int     exec_exit(char **argv, t_shell *shell)
{
    (void)argv;
    shell->should_exit = 1;
    return (shell->last_status);
}
