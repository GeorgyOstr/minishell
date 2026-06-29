/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hisasano <hisasano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 22:13:00 by hisasano          #+#    #+#             */
/*   Updated: 2026/06/29 19:54:18 by hisasano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "token.h"

typedef struct s_shell	t_shell;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR
}						t_node_type;

// NODE_CMD, ls -a
// NODE_PIPE,　|
// NODE_REDIR　> >> < <<

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}						t_redir_type;

typedef struct s_ast
{
	t_node_type			type;
	char				**argv;
	int					redir_type;
	char				*file;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

t_ast					*parse_pipe(t_token *tokens, int start, int end);
t_ast					*parse_command(t_token *tokens, int start, int end);
t_ast					*new_node(t_node_type type);
void					free_ast(t_ast *node);
int						add_word(t_ast *node, char *value);
int						exec_ast(t_shell *shell, t_ast *node);
int						exec_cmd(t_shell *shell, t_ast *node);
char					*find_cmd_path(char *cmd, char **envp);
int						exec_redir(t_shell *shell, t_ast *node);
int						exec_heredoc(t_shell *shell, t_ast *node);
int						exec_pipe(t_shell *shell, t_ast *node);

#endif
