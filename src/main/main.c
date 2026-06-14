/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:30:22 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/14 20:03:24 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    (void) ac;
    (void) av;
    return(minishell(envp));
}

// #include <stdlib.h>
// #include <unistd.h>

// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// // #include <signal.h>

// int main()
// {
//     char *line;

//     rl_outstream = stderr;
//     while(1)
//     {
//         line = readline("minishell$ ");
//         if (line == NULL)
//             break;
//         if (*line)
//             add_history(line);
//         free(line);
//     }
//     exit(0);
// }
