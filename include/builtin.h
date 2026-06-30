/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 20:11:54 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/27 23:11:42 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "shell.h"

int	is_builtin(char *cmd);
int	exec_builtin(t_shell *shell, char **argv);
int	exec_echo(char **argv);
int	exec_pwd(void);
int	exec_cd(char **argv, t_shell *shell);
int	exec_env(char **argv, t_shell *shell);
int	exec_export(char **argv, t_shell *shell);
int	exec_unset(char **argv, t_shell *shell);
int	exec_exit(char **argv, t_shell *shell);
int	set_env_var(t_shell *shell, char *key, char *val);
int	print_export(char **envp);

#endif