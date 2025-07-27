PRINTF_DIR = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
LIBFT_DIR = $(PRINTF_DIR)libft

CC				= cc
RM				= rm -f
CFLAGS		= -Wall -Wextra -Werror
AR				= ar rcs

LIBFT = $(LIBFT_DIR)/libft.a
NAME = libftprintf.a

SRCS = \
	$(addprefix $(PRINTF_DIR)/, \
		ft_printf.c put_type_helpers.c put_type_c.c put_type_s.c \
		put_type_p.c put_type_d.c put_type_u.c put_type_x.c \
	)

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
	$(AR) $(NAME) $(OBJS) $(LIBFT_DIR)/*.o

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean:	clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY:	all clean fclean re
