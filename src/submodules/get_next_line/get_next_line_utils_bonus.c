/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:33:14 by haatwata          #+#    #+#             */
/*   Updated: 2025/02/10 21:33:46 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*ft_memset(void *s, int c, size_t len)
{
	size_t			i;
	unsigned char	*t;

	t = (unsigned char *)s;
	i = 0;
	while (i < len)
	{
		*t = (unsigned char)c;
		t++;
		i++;
	}
	return (s);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

static bool	is_valid(size_t count, size_t size)
{
	if (count > SIZE_MAX / size)
		return (false);
	return (true);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret;

	if (count != 0 && size != 0 && !is_valid(count, size))
		return (NULL);
	ret = (unsigned char *)malloc(size * count);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, size * count);
	return ((void *)ret);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	ind;
	char	*_dst;
	char	*_src;

	if (dst == NULL && src == NULL)
		return (dst);
	_dst = (char *)dst;
	_src = (char *)src;
	ind = 0;
	while (ind < n)
	{
		*_dst = *_src;
		_dst++;
		_src++;
		ind++;
	}
	return (dst);
}
