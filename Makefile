# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/01 12:55:36 by hisasano          #+#    #+#              #
#    Updated: 2026/07/01 14:37:55 by gostroum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

#################
# Directories   #
#################

SRC_DIR		= src
INC_DIR		= include
LIBFT_DIR	= $(SRC_DIR)/libft

#################
# Includes      #
#################

INCLUDES	= -I$(INC_DIR) \
			  -I$(LIBFT_DIR)/include

#################
# Libft         #
#################

LIBFT		= $(LIBFT_DIR)/libft.a

#################
# Sources       #
#################

SRCS		= \
	$(SRC_DIR)/main/main.c \
	$(SRC_DIR)/main/minishell.c \
	$(SRC_DIR)/main/read_line_loop.c \
	$(SRC_DIR)/main/make_cmd.c \
	$(SRC_DIR)/main/signals.c \
	$(SRC_DIR)/lexer/lexer_is.c \
	$(SRC_DIR)/lexer/lexer.c \
	$(SRC_DIR)/parser/parse_pipe.c \
	$(SRC_DIR)/parser/parse_command.c \
	$(SRC_DIR)/parser/add_word.c \
	$(SRC_DIR)/utils/free_arr.c \
	$(SRC_DIR)/utils/free_tokens.c\
	$(SRC_DIR)/execve/exec_ast.c \
	$(SRC_DIR)/execve/exec_pipe.c \
	$(SRC_DIR)/execve/find_cmd_path.c \
	$(SRC_DIR)/execve/exec_utils.c \
	$(SRC_DIR)/builtin/builtin.c \
	$(SRC_DIR)/builtin/builtin_echo.c \
	$(SRC_DIR)/builtin/builtin_pwd.c \
	$(SRC_DIR)/builtin/builtin_cd.c \
	$(SRC_DIR)/builtin/builtin_env.c \
	$(SRC_DIR)/builtin/builtin_exit.c \
	$(SRC_DIR)/builtin/builtin_export.c \
	$(SRC_DIR)/builtin/export_env.c \
	$(SRC_DIR)/builtin/export_print.c \
	$(SRC_DIR)/builtin/builtin_unset.c \
	$(SRC_DIR)/execve/exec_redir.c \
	$(SRC_DIR)/execve/exec_heredoc.c \
	$(SRC_DIR)/expander/expand_word.c \
	$(SRC_DIR)/expander/expand_dollar.c \
	$(SRC_DIR)/expander/expand_utils.c \
	$(SRC_DIR)/expander/expand_ast.c \
	$(SRC_DIR)/execve/exec_redir_prepare.c

OBJS		= $(SRCS:.c=.o)

#################
# Readline      #
#################

UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	READLINE_PREFIX := $(shell brew --prefix readline)
	INCLUDES += -I$(READLINE_PREFIX)/include
	LIBS	= -L$(READLINE_PREFIX)/lib -lreadline
else
	LIBS	= -lreadline
endif

#################
# Rules         #
#################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re