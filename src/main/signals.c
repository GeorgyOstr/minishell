/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 00:00:00 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/30 00:00:00 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_signal = 0;

/*
** Interactive prompt handler: on Ctrl+C, move to a fresh line, drop the
** current input and redisplay an empty prompt.
*/
static void	prompt_sigint_handler(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
** Signals while waiting at the prompt:
**   Ctrl+C  -> reset the line and redisplay the prompt.
**   Ctrl+\  -> ignored.
*/
void	setup_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = prompt_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
** Signals while a command is running: the parent ignores both so that
** Ctrl+C / Ctrl+\ only reach the foreground child process.
*/
void	setup_signals_exec(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/*
** Restore the default behavior in child processes before execve, so that
** Ctrl+C terminates them and Ctrl+\ quits with a core dump.
*/
void	setup_signals_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
