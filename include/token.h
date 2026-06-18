/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:52:15 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/17 18:40:02 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

int     lexer(t_token **tokens, char *line);
void	free_tokens(t_token *token);
void	print_tokens(t_token *token);

#endif

	// T_WORD, = str
	// T_PIPE, =  |
	// T_REDIR_IN, = <
	// T_REDIR_OUT, = >
	// T_APPEND, = >>
	// T_HEREDOCv = <<