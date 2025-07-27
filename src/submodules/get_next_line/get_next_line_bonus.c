/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:32:51 by haatwata          #+#    #+#             */
/*   Updated: 2025/02/10 21:33:43 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	int	ft_getc(int fd)
{
	static t_file	file[OPEN_MAX];
	ssize_t			tmp;

	if (file[fd].n == (ssize_t)0)
	{
		tmp = read(fd, file[fd].buf, BUFFER_SIZE);
		if (tmp == (ssize_t)(-1))
			return (-2);
		file[fd].n = tmp;
		file[fd].buf_head = file[fd].buf;
	}
	if ((ssize_t)0 < file[fd].n)
	{
		file[fd].n--;
		return ((int)*file[fd].buf_head++);
	}
	else
	{
		return (EOF);
	}
}

static void	appendc(t_string *s, char c)
{
	char	*tmp;

	if (s->buf_size <= s->len)
	{
		if (s->buf_size == (ssize_t)0)
		{
			s->buf_size = (ssize_t)42;
			s->buf = (char *)ft_calloc(s->buf_size, sizeof(char));
			if (s->buf == NULL)
				return ;
		}
		else
		{
			tmp = s->buf;
			s->buf_size *= 2;
			s->buf = (char *)ft_calloc(s->buf_size, sizeof(char));
			if (s->buf == NULL)
				return ;
			ft_memcpy(s->buf, tmp, s->len);
			free(tmp);
		}
	}
	s->buf[s->len++] = c;
}

static void	init_string(t_string *string)
{
	string->buf = NULL;
	string->len = (ssize_t)0;
	string->buf_size = (ssize_t)0;
}

static char	*return_process(t_string *string, int new_c)
{
	if (new_c == -2)
	{
		if (string->buf != NULL)
			free(string->buf);
		return (NULL);
	}
	if (string->buf != NULL)
		appendc(string, '\0');
	return (string->buf);
}

char	*get_next_line(int fd)
{
	int				new_c;
	t_string		string;

	if (fd < 0 || OPEN_MAX <= fd || BUFFER_SIZE <= 0)
		return (NULL);
	init_string(&string);
	while (1)
	{
		new_c = ft_getc(fd);
		if (new_c == EOF || new_c == -2)
			break ;
		appendc(&string, new_c);
		if (string.buf == NULL)
			return (NULL);
		if (new_c == '\n')
			break ;
	}
	return (return_process(&string, new_c));
}

// #include <fcntl.h>
// #include <stdio.h>
// int main(void) {
//     int fd;
//     // int fd2;

//     fd = open("get_next_line.c", O_RDONLY);
//     // fd2 = open("get_next_line.h", O_RDONLY);

//     // test ft_getc
//     // while (1) {
//     //     int c = ft_getc(fd);
//     //     if (c == (-1))
//     //       break;
//     //     printf("%c", c);
//     // }

//     // test get_next_line
//     while (1)
//     {
//       char *s = get_next_line(fd);
//       // char *s2 = get_next_line(fd2);
//       if (s == NULL)
//       {
//         break;
//       }
//       if (s != NULL)
//       {
//         printf("%s", s);
//       }
//       // if (s2 != NULL)
//       // {
//       //   printf("%s", s2);
//       // }
//     }

//     close(fd);
//     return (0);
// }
