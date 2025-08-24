/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_type_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:02:51 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/10 04:15:32 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_type_s(va_list *ap, int width, int fd)
{
	char		*content;
	size_t		content_len;
	int			ret;

	content = va_arg(*ap, char *);
	if (content == NULL)
	{
		ft_putstr_fd("(null)", fd);
		ret = 6;
	}
	else
	{
		content_len = ft_strlen(content);
		if (content_len < (size_t)width)
		{
			put_space(width - content_len, fd);
			ret = width;
		}
		else
			ret = content_len;
		ft_putstr_fd(content, fd);
	}
	return (ret);
}
