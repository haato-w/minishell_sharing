/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_type_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:02:47 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/10 04:15:18 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ptr_len(uintptr_t ptr_uint)
{
	int	i;

	i = 0;
	while (ptr_uint > 0)
	{
		ptr_uint /= 16;
		i++;
	}
	return (i);
}

static int	put_address(void *content, int width, int fd)
{
	uintptr_t	content_uint;
	int			content_len;
	int			ret;

	content_uint = (uintptr_t)content;
	content_len = ptr_len(content_uint) + 2;
	if (content_len < width)
	{
		put_space(width - content_len, fd);
		ret = width;
	}
	else
		ret = content_len;
	put_ptr_as_hex(content_uint, fd);
	return (ret);
}

int	put_type_p(va_list *ap, int width, int fd)
{
	void		*content;
	int			ret;

	content = va_arg(*ap, void *);
	if (content == NULL)
	{
		ft_putstr_fd("(nil)", fd);
		ret = 5;
	}
	else
		ret = put_address(content, width, fd);
	return (ret);
}
