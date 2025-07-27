/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:11:10 by haatwata          #+#    #+#             */
/*   Updated: 2024/08/18 19:03:44 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if ('A' <= (char)c && (char)c <= 'Z')
	{
		c += 32;
	}
	return (c);
}

// #include <stdio.h>
// int main(void)
// {
//         char c1 = 'h';
//         printf("%c\n", ft_tolower(c1));
//         char c2 = ' ';
//         printf("%c\n", ft_tolower(c2));
//         char c3 = 'L';
//         printf("%c\n", ft_tolower(c3));
//         char c4 = '1';
//         printf("%c\n", ft_tolower(c4));
//         char c5 = '!';
//         printf("%c\n", ft_tolower(c5));
// }
