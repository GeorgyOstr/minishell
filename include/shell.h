/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:42:54 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/19 14:51:05 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <signal.h>
# include "command.h"

typedef struct s_shell
{
    char **envp;
    int last_status;
    int should_exit;
    t_ast *node;
}   t_shell;

// i int last_status;　
// Exit status of the last executed command

extern volatile sig_atomic_t	g_signal;

int minishell(char **envp);
void read_line_loop(t_shell *shell);
int	make_cmd(t_shell *shell, char *line);

void	setup_signals_interactive(void);
void	setup_signals_exec(void);
void	setup_signals_child(void);

#endif
