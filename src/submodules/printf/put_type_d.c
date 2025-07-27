/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_type_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:02:38 by haatwata          #+#    #+#             */
/*   Updated: 2025/02/08 12:36:20 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_type_d(va_list *ap, int width)
{
	int			content;
	char		*content_str;
	size_t		content_len;
	int			ret;

	content = va_arg(*ap, int);
	content_str = ft_itoa(content);
	content_len = ft_strlen(content_str);
	if (content_len < (size_t)width)
	{
		put_space(width - content_len);
		ret = width;
	}
	else
	{
		ret = content_len;
	}
	ft_putstr_fd(content_str, 1);
	free(content_str);
	return (ret);
}
