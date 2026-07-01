/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:42:54 by hisasano          #+#    #+#             */
/*   Updated: 2026/07/01 13:41:21 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "command.h"
# include <signal.h>

typedef struct s_shell
{
	char						**envp;
	int							last_status;
	int							should_exit;
	t_ast						*node;
}								t_shell;

extern volatile sig_atomic_t	g_signal;

int								minishell(char **envp);
void							read_line_loop(t_shell *shell);
int								make_cmd(t_shell *shell, char *line);

void							setup_signals_interactive(void);
void							setup_signals_exec(void);
void							setup_signals_child(void);

#endif
