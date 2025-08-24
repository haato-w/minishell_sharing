/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:06:25 by haatwata          #+#    #+#             */
/*   Updated: 2024/04/18 20:55:59 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	char c1 = '1';
// 	printf("%d\n", ft_isdigit(c1));
// 	char c2 = '3';
//         printf("%d\n", ft_isdigit(c2));
// 	char c3 = '9';
//         printf("%d\n", ft_isdigit(c3));
// 	char c4 = 'a';
//         printf("%d\n", ft_isdigit(c4));
// 	char c5 = '!';
//         printf("%d\n", ft_isdigit(c5));
// }
