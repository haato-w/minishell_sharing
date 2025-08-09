MINISHELL_DIR = .
PRINTF_DIR = $(MINISHELL_DIR)/submodules/printf
GNL_DIR = $(MINISHELL_DIR)/submodules/get_next_line

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LIBS		= -lreadline
SRCS		= main.c\
					utils/error.c\
					utils/destructor.c\
					utils/ft_strndup.c\
					utils/ft_xstrdup.c\
					utils/ft_xstrndup.c\
					utils/ft_xcalloc.c\
					expand/expand.c\
					tokenize/tokenize.c\
					tokenize/tokenize_utils.c\
					tokenize/argv.c\
					tokenize/word.c\
					parse/parse.c\
					parse/parse_utils.c\
					parse/parse_redirect.c\
					parse/node.c\
					redirect/redirect.c\
					pipe.c\
					exec/exec.c\
					exec/search_path.c\
					exec/validate_access.c\
					signal/signal.c\
					builtin/builtin.c\
					builtin/builtin_exit.c\
					builtin/builtin_export.c\
					builtin/builtin_unset.c\
					builtin/builtin_env.c\
					builtin/builtin_cd.c\
					builtin/builtin_echo.c\
					builtin/builtin_pwd.c\
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
