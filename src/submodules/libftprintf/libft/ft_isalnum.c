/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:56:36 by haatwata          #+#    #+#             */
/*   Updated: 2024/08/18 18:02:07 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || \
			('a' <= c && c <= 'z'))
		return (1);
	return (0);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char c1 = '0';
// 	char c2 = '9';
// 	char c3 = 'A';
// 	char c4 = 'f';
// 	char c5 = '!';
// 	printf("%d\n", ft_isalnum(c1));
// 	printf("%d\n", ft_isalnum(c2));
// 	printf("%d\n", ft_isalnum(c3));
// 	printf("%d\n", ft_isalnum(c4));
// 	printf("%d\n", ft_isalnum(c5));
// }
