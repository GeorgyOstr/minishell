/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:42:54 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/14 20:17:34 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_shell
{
    char **envp;
    int last_status;
    int should_exit;
}   t_shell;

// i int last_status;　
// Exit status of the last executed command

int minishell(char **envp);

#endif
