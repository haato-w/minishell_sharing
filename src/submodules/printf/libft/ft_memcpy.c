/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:25:37 by haatwata          #+#    #+#             */
/*   Updated: 2024/08/18 18:27:25 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	ind;
	char	*_dst;
	char	*_src;

	if (dst == NULL && src == NULL)
		return (dst);
	_dst = (char *)dst;
	_src = (char *)src;
	ind = 0;
	while (ind < n)
	{
		*_dst = *_src;
		_dst++;
		_src++;
		ind++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	int N = 3;
// 	char a[] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
// 	char b[] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};

// 	char *c = (char *)ft_memcpy(a, b, 0);

// 	int i = 0;
// 	while (i < N)
// 	{
// 		printf("%c", a[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	i = 0;
// 	while (i < N)
// 	{
// 		printf("%c", c[i]);
// 		i++;
// 	}

// 	return (0);
// }
