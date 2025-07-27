/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:11:10 by haatwata          #+#    #+#             */
/*   Updated: 2024/04/19 20:30:22 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c <= 31 || 127 <= c)
		return (0);
	return (1);
}

// #include <stdio.h>
// int main(void)
// {
//         char c1 = 127;
//         printf("%d\n", ft_isprint(c1));
//         char c2 = 0;
//         printf("%d\n", ft_isprint(c2));
//         char c3 = 'a';
//         printf("%d\n", ft_isprint(c3));
//         char c4 = '1';
//         printf("%d\n", ft_isprint(c4));
//         char c5 = ' ';
//         printf("%d\n", ft_isprint(c5));
// }
