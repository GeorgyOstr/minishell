/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:56:01 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/14 22:37:10 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

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
    make_cmd(shell, line);//Lexer → Perser
    do_cmd(shell);
    clear_cmd(shell);
}

static int     is_only_space(char *line)
{
        

}