/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:43:18 by haatwata          #+#    #+#             */
/*   Updated: 2024/04/19 21:03:51 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int N = 10;
// 	char a[N];
// 	int i = 0;
// 	ft_bzero(a, N);
// 	a[N - 1] = '\0';
// 	while (i < N)
// 	{
// 		printf("%d", a[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }
