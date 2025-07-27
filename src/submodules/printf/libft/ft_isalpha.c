/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:45:25 by haatwata          #+#    #+#             */
/*   Updated: 2024/08/18 18:03:12 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1);
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	char c1 = 'a';
// 	printf("%d\n", ft_isalpha(c1));
// 	char c2 = 'f';
// 	printf("%d\n", ft_isalpha(c2));
// 	char c3 = 'A';
//         printf("%d\n", ft_isalpha(c3));
// 	char c4 = 'Z';
//         printf("%d\n", ft_isalpha(c4));
// 	char c5 = '1';
//         printf("%d\n", ft_isalpha(c5));
// }
