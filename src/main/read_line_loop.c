/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:56:01 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/17 19:26:00 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static int     is_only_space(char *line);
void read_line_loop(t_shell *shell);
static void    handle_line(t_shell *shell, char *line);

static int     is_only_space(char *line)
{
    while(line)
    {
        if(*line != ' ')
            return (0);
    }
    return (1);
}

void read_line_loop(t_shell *shell)
{
    // (void)shell;
    char *line;

    while(1)
    {
        line = readline("minishell$ ");
        if (line == NULL)
            break ;
        handle_line(shell, line);
        free(line);
    }
    return ;
}

void    handle_line(t_shell *shell, char *line)
{
    if (line[0] != '\0')
        add_history(line);
    if (is_only_space(line))
        return ;
    if (make_cmd(shell, line))
        return ;//Lexer → Perser
    // if (do_cmd(shell))
    //     return ;
    // clear_cmd(shell);
}
