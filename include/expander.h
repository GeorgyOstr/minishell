/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:03:15 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/30 17:17:19 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_shell	t_shell;
typedef struct s_ast	t_ast;

int						is_env_name_char(char c);
char					*append_expanded_str(char *left, char *right);
char					*append_expanded_char(char *str, char c);
char					*expand_dollar(char *res, char *word, int *i,
							t_shell *shell);
char					*expand_word(char *word, t_shell *shell);
int						expand_ast(t_ast *node, t_shell *shell);

#endif
