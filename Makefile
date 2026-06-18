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
	$(SRC_DIR)/utils/free_arr.c \
	$(SRC_DIR)/lexer/lexer.c \
	$(SRC_DIR)/main/make_cmd.c \
	$(SRC_DIR)/utils/clear_cmd.c \
	$(SRC_DIR)/utils/free_tokens.c\
# 	$(SRC_DIR)/do_cmd/do_cmd.c 

OBJS		= $(SRCS:.c=.o)

#################
# Readline      #
#################

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	READLINE_PREFIX := $(shell brew --prefix readline)
	INCLUDES += -I$(READLINE_PREFIX)/include
	LIBS = -L$(READLINE_PREFIX)/lib -lreadline
else
	LIBS = -lreadline
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
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "clean complete"

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@echo "fclean complete"

re: fclean all

.PHONY: all clean fclean re