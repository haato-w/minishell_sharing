/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:11:10 by haatwata          #+#    #+#             */
/*   Updated: 2024/08/18 19:04:30 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if ('a' <= (char)c && (char)c <= 'z')
		c -= 32;
	return (c);
}

// #include <stdio.h>
// int main(void)
// {
//         char c1 = 'h';
//         printf("%c\n", ft_toupper(c1));
//         char c2 = '1';
//         printf("%c\n", ft_toupper(c2));
//         char c3 = ' ';
//         printf("%c\n", ft_toupper(c3));
//         char c4 = 'H';
//         printf("%c\n", ft_toupper(c4));
//         char c5 = '!';
//         printf("%c\n", ft_toupper(c5));
// }
