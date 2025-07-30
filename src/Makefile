MINISHELL_DIR = .
PRINTF_DIR = $(MINISHELL_DIR)/submodules/printf
GNL_DIR = $(MINISHELL_DIR)/submodules/get_next_line

NAME	= minishell
PRINTF = $(PRINTF_DIR)/libftprintf.a

CC		= cc
RLDIR = $(shell brew --prefix readline)
INCLUDES = -I ./ -I$(PRINTF_DIR) -I$(RLDIR)/include
CFLAGS	= -Wall -Wextra -Werror $(INCLUDES) -fPIE
LIBS		= -lreadline -L$(RLDIR)/lib
SRCS		= main.c\
					error.c\
					tokenize.c\
					destructor.c\
					expand.c\
					parse.c\
					redirect.c\
					pipe.c\
					builtin.c\

OBJS		= $(SRCS:%.c=%.o)

all: $(NAME)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(NAME): $(OBJS) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(PRINTF) -pie -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make -C $(PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(PRINTF_DIR) fclean

re: fclean all

test: all
	./test.sh

.PHONY: all clean fclean re test
