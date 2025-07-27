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

OBJS		= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	./test.sh

.PHONY: all clean fclean re test
