/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:00:38 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 16:26:28 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	consume_path(char **rest, char *path, char *elem)
{
	size_t	elem_len;

	elem_len = strlen(elem);
	if (strncmp(path, elem, elem_len) == 0)
	{
		if (path[elem_len] == '\0' || path[elem_len] == '/')
		{
			*rest = path + elem_len;
			return (true);
		}
	}
	return (false);
}

void	delete_last_elem(char *path)
{
	char	*start;
	char	*last_slash_ptr;

	start = path;
	last_slash_ptr = NULL;
	while (*path)
	{
		if (*path == '/')
			last_slash_ptr = path;
		path++;
	}
	if (last_slash_ptr != start)
		*last_slash_ptr = '\0';
}

size_t	strlncpy(char *dst, char *src, size_t n, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && n > 0 && *src)
	{
		dst[i] = *src;
		src++;
		i++;
		n--;
	}
	dst[i] = '\0';
	while (n > 0 && *src)
	{
		i++;
		n--;
		src++;
	}
	return (i);
}

void	append_path_elem(char *dst, size_t dstsize, char **rest, char *src)
{
	char	buf[PATH_MAX];
	size_t	elem_len;

	elem_len = 0;
	while (src[elem_len] && src[elem_len] != '/')
		elem_len++;
	if (strlncpy(buf, src, elem_len, PATH_MAX) >= PATH_MAX)
		assert_error("strlncpy error");
	if (dst[ft_strlen(dst) - 1] != '/')
		if (ft_strlcat(dst, "/", dstsize) >= dstsize)
			assert_error("This will not happen");
	if (ft_strlcat(dst, buf, dstsize) >= dstsize)
		assert_error("ft_strlcat error");
	*rest = src + elem_len;
}
