/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:33:26 by haatwata          #+#    #+#             */
/*   Updated: 2025/02/08 22:20:07 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define OPEN_MAX 1000

typedef struct s_file
{
	char		buf[BUFFER_SIZE];
	char		*buf_head;
	ssize_t		n;
}	t_file;

typedef struct s_string
{
	char		*buf;
	size_t		len;
	size_t		buf_size;
}	t_string;

char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
