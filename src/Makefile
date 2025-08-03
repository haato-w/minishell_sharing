MINISHELL_DIR = .
PRINTF_DIR = $(MINISHELL_DIR)/submodules/printf
GNL_DIR = $(MINISHELL_DIR)/submodules/get_next_line

NAME	= minishell
CC		= cc
# INCLUDES = -I include
# CFLAGS	= -Wall -Wextra -Werror $(INCLUDES)
CFLAGS	= -Wall -Wextra -Werror
LIBS		= -lreadline
SRCS		= main.c\
					error.c\
					tokenize.c\
					destructor.c\
					expand.c\
					parse.c\
					redirect.c\
					pipe.c\
					exec.c\
					signal.c\
					builtin.c\
					builtin_exit.c\
					builtin_export.c\
					builtin_unset.c\
					map.c\
					env.c\


PRINTF = $(PRINTF_DIR)/libftprintf.a

OBJS		= $(SRCS:%.c=%.o)

# for MAC
CFLAGS += -I/opt/homebrew/opt/readline/include
LIBS += -L/opt/homebrew/opt/readline/lib -lreadline -lncurses

all: $(NAME)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(NAME): $(OBJS) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(PRINTF) -I$(PRINTF_DIR) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(PRINTF_DIR) -O3 -c $< -o $@

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
