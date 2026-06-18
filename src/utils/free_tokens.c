/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:53:15 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/17 19:32:14 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "minishell.h"

void free_tokens(t_token *tokens);

void free_tokens(t_token *tokens)
{
    t_token *next;

    while(tokens)
    {
        next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}
