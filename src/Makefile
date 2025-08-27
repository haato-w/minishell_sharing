MINISHELL_DIR	= .
LIBFTPRINTF_DIR	= $(MINISHELL_DIR)/submodules/libftprintf
LIBFT_DIR		= $(MINISHELL_DIR)/submodules/libftprintf/libft

NAME	= minishell
CC		= cc
# CFLAGS	= -Wall -Wextra -Werror
# CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=leak -fsanitize=address

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS	= -lreadline
endif
ifeq ($(UNAME_S),Darwin) # for MAC
	LIBS	= -L/opt/homebrew/opt/readline/lib -lreadline -lncurses
    CFLAGS	+= -I/opt/homebrew/opt/readline/include
endif

SRCS		=	main.c\
				utils/error.c\
				utils/syntax_error.c\
				utils/error_exit.c\
				utils/destructor.c\
				utils/ft_strcmp.c\
				utils/ft_strndup.c\
				utils/ft_xstrdup.c\
				utils/ft_xstrndup.c\
				utils/ft_xcalloc.c\
				utils/ft_xclose.c\
				utils/ft_xdup2.c\
				utils/ft_atoll.c\
				tokenize/tokenize.c\
				tokenize/tokenize_utils.c\
				tokenize/argv.c\
				tokenize/word.c\
				parse/parse.c\
				parse/parse_utils.c\
				parse/parse_redirect.c\
				parse/node.c\
				expand/expand.c\
				expand/expand_quote_removal.c\
				expand/expand_variable.c\
				expand/expand_utils.c\
				redirect/redirect.c\
				redirect/open_redir_file.c\
				redirect/heredoc.c\
				pipe.c\
				exec/exec.c\
				exec/search_path.c\
				exec/validate_access.c\
				signal/signal.c\
				signal/input_sig.c\
				signal/execution_sig.c\
				signal/heredoc_sig.c\
				builtin/builtin.c\
				builtin/builtin_exit.c\
				builtin/builtin_export.c\
				builtin/builtin_unset.c\
				builtin/builtin_env.c\
				builtin/builtin_cd.c\
				builtin/path_funcs.c\
				builtin/builtin_echo.c\
				builtin/builtin_pwd.c\
				environ/env.c\
				environ/map.c\
				environ/map_set.c\
				environ/map_item.c\
				environ/map_put.c\
				environ/map_unset.c\

LIBFTPRINTF = $(LIBFTPRINTF_DIR)/libftprintf.a

OBJS		= $(SRCS:%.c=%.o)

all: $(NAME)

$(LIBFTPRINTF):
	@make -C $(LIBFTPRINTF_DIR)

$(NAME): $(OBJS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFTPRINTF) -I$(LIBFTPRINTF_DIR) -I$(LIBFT_DIR) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFTPRINTF_DIR) -I$(LIBFT_DIR) -O3 -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFTPRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFTPRINTF_DIR) fclean

re: fclean all

test: all
	./test.sh

.PHONY: all clean fclean re test
