/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_type_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:02:42 by haatwata          #+#    #+#             */
/*   Updated: 2025/02/09 16:24:22 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_space(int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
}

void	put_ptr_as_hex(uintptr_t ptr_uint)
{
	char	*hex_digits;
	char	reverse_buffer[17];
	char	buffer[17];
	int		i;
	int		j;

	hex_digits = "0123456789abcdef";
	reverse_buffer[0] = '\0';
	i = 1;
	while (ptr_uint > 0)
	{
		reverse_buffer[i++] = hex_digits[ptr_uint % 16];
		ptr_uint /= 16;
	}
	j = 0;
	while (j < i)
	{
		buffer[j] = reverse_buffer[i - j - 1];
		j++;
	}
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(buffer, 1);
}

int	base_n_len(unsigned int value, unsigned int n)
{
	int	i;

	if (value == 0)
		return (1);
	i = 0;
	while (value > 0)
	{
		value /= n;
		i++;
	}
	return (i);
}

static void	reverse_buffer(
	int buf_len, char *buffer, char *rev_buffer, bool is_big)
{
	int		j;

	j = 0;
	while (j < buf_len)
	{
		buffer[j] = rev_buffer[buf_len - j - 1];
		if (is_big)
			buffer[j] = ft_toupper(buffer[j]);
		j++;
	}
}

void	put_as_base_n(unsigned int value, unsigned int n, bool is_big)
{
	char	*hex_digits;
	char	rev_buffer[17];
	char	buffer[17];
	int		i;

	hex_digits = "0123456789abcdef";
	if (value == 0)
	{
		ft_putchar_fd(hex_digits[0], 1);
		return ;
	}
	rev_buffer[0] = '\0';
	i = 1;
	while (value > 0)
	{
		rev_buffer[i++] = hex_digits[value % n];
		value /= n;
	}
	reverse_buffer(i, buffer, rev_buffer, is_big);
	ft_putstr_fd(buffer, 1);
}
