/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:27:43 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:28:18 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	ind;
	char	*_dst;
	char	*_src;

	if (dst == src)
		return (dst);
	_dst = (char *)dst;
	_src = (char *)src;
	if (dst <= src)
	{
		ft_memcpy(dst, src, len);
	}
	else
	{
		ind = 0;
		while (ind < len)
		{
			_dst[len - ind - 1] = _src[len - ind - 1];
			ind++;
		}
	}
	return (dst);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int N = 10;
// 	char a[] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
// 	char b[] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};

// 	char *c = (char *)ft_memmove(a, a, 10);

// 	int i = 0;
// 	while (i < N)
// 	{
// 		printf("%c", c[i]);
// 		i++;
// 	}
// 	printf("\n");

// 	c = (char *)ft_memmove(a, b, 10);

// 	i = 0;
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
//   	printf("\n");

// 	return (0);
// }
