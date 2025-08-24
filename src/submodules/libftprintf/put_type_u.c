/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_type_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:02:54 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/10 04:15:59 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_type_u(va_list *ap, int width, int fd)
{
	unsigned int	content;
	int				content_len;
	int				ret;

	content = va_arg(*ap, unsigned int);
	content_len = base_n_len(content, (unsigned int)10);
	if (content_len < width)
	{
		put_space(width - content_len, fd);
		ret = width;
	}
	else
	{
		ret = content_len;
	}
	put_as_base_n(content, (unsigned int)10, false, fd);
	return (ret);
}
