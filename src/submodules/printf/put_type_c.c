/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_type_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:02:33 by haatwata          #+#    #+#             */
/*   Updated: 2025/02/09 15:08:21 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_type_c(va_list *ap, int width)
{
	char	content;
	int		ret;

	content = va_arg(*ap, int);
	if (1 < width)
	{
		put_space(width - 1);
		ret = width;
	}
	else
		ret = 1;
	ft_putchar_fd(content, 1);
	return (ret);
}
