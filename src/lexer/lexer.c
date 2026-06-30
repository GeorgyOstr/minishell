/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:40:59 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/27 22:31:05 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

static int		is_space(char c);
static int		is_operator(char c);
static size_t	word_len(char *str);
static int		add_operator(t_token **tokens, char *line, int i);
static t_token	*new_token(char *value, t_token_type type);
static void		add_token(t_token **head, t_token *new);
int				lexer(t_token **tokens, char *line);

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static size_t	word_len(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i] && !is_space(str[i]) && !is_operator(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
			i++;
	}
	return (i);
}

static int	add_operator(t_token **tokens, char *line, int i)
{
	if (line[i] == '|')
		add_token(tokens, new_token(ft_strdup("|"), T_PIPE));
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		add_token(tokens, new_token(ft_strdup("<<"), T_HEREDOC));
		return (i + 2);
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		add_token(tokens, new_token(ft_strdup(">>"), T_APPEND));
		return (i + 2);
	}
	else if (line[i] == '<')
		add_token(tokens, new_token(ft_strdup("<"), T_REDIR_IN));
	else if (line[i] == '>')
		add_token(tokens, new_token(ft_strdup(">"), T_REDIR_OUT));
	return (i + 1);
}

static t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*cur;

	if (!*head)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return ;
}

int	lexer(t_token **tokens, char *line)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		if (is_operator(line[i]))
			i = add_operator(tokens, line, i);
		else
		{
			len = word_len(&line[i]);
			add_token(tokens, new_token(ft_substr(line, i, len), T_WORD));
			i += len;
		}
	}
	return (0);
}

// T_WORD, = str
// T_PIPE, =  |
// T_REDIR_IN, = <
// T_REDIR_OUT, = >
// T_APPEND, = >>
// T_HEREDOC = <<