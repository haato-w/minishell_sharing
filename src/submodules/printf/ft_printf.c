/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:02:15 by haatwata          #+#    #+#             */
/*   Updated: 2025/02/09 16:06:06 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_specifier_content(const char *format, va_list *ap, int width)
{
	if (*format == 'c')
		return (put_type_c(ap, width));
	else if (*format == 's')
		return (put_type_s(ap, width));
	else if (*format == 'p')
		return (put_type_p(ap, width));
	else if (*format == 'd')
		return (put_type_d(ap, width));
	else if (*format == 'i')
		return (put_type_d(ap, width));
	else if (*format == 'u')
		return (put_type_u(ap, width));
	else if (*format == 'x')
		return (put_type_x(ap, width, false));
	else if (*format == 'X')
		return (put_type_x(ap, width, true));
	else if (*format == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (0);
}

static int	process_specifier(const char **format, va_list *ap)
{
	int	width;
	int	ret;

	(*format)++;
	width = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
	ret = put_specifier_content(*format, ap, width);
	(*format)++;
	return (ret);
}

static int	ft_vprintf(const char *format, va_list *ap)
{
	size_t	ret;

	ret = 0;
	while (*format)
	{
		if (*format == '%')
			ret += process_specifier(&format, ap);
		else
		{
			ft_putchar_fd(*format, 1);
			format++;
			ret++;
		}
	}
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	ret;

	va_start(ap, format);
	ret = ft_vprintf(format, &ap);
	va_end(ap);
	return (ret);
}

// #include <stdio.h>
// int main()
// {
//   ft_printf("hello");
//   ft_printf(" world\n");
//   printf("hello");
//   printf(" world\n");

//   ft_printf("i: %10d!!%2c, !, %4s\n", 10, 'a', "hello");
//   printf("i: %10d!!%2c, !, %4s\n", 10, 'a', "hello");

//   int a;
//   ft_printf("p: %p\n", &a);
//   printf("p: %p\n", &a);

//   ft_printf("%3u, %3u, %3x, %3x, %3X, %3X\n", 10, -1, 10, -1, 10, -1);
//   printf("%3u, %3u, %3x, %3x, %3X, %3X\n", 10, -1, 10, -1, 10, -1);

//   ft_printf("%%%i\n", 1);
//   printf("%%%i\n", 1);

//   ft_printf("%c", '0');
//   printf("%c", '0');

//   return (0);
// }
