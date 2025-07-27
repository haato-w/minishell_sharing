/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:17:29 by haatwata          #+#    #+#             */
/*   Updated: 2024/04/19 14:23:29 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	return (0);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char c1 = '0';
// 	char c2 = 'a';
// 	char c3 = '!';
// 	char c4 = ' ';
// 	printf("%d\n", ft_isascii(c1));
// 	printf("%d\n", ft_isascii(c2));
// 	printf("%d\n", ft_isascii(c3));
// 	printf("%d\n", ft_isascii(c4));
// 	printf("%d\n", ft_isascii(300));
// }
