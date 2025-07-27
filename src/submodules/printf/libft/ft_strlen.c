/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:49:49 by haatwata          #+#    #+#             */
/*   Updated: 2024/04/19 20:38:43 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		s++;
		cnt++;
	}
	return (cnt);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s = "hello";
// 	printf("%zu\n", ft_strlen(s));
// }
