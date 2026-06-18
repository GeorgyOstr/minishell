/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:42:54 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/17 19:25:48 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "command.h"

typedef struct s_shell
{
    char **envp;
    int last_status;
    int should_exit;
    t_cmd *cmd;
}   t_shell;

// i int last_status;　
// Exit status of the last executed command

int minishell(char **envp);
void read_line_loop(t_shell *shell);
int	make_cmd(t_shell *shell, char *line);

#endif
