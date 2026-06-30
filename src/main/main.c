/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:30:22 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/25 19:00:00 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "shell.h"

int main(int ac, char **av, char **envp)
{
    (void) ac;
    (void) av;
    return(minishell(envp));
}
