/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:43:18 by haatwata          #+#    #+#             */
/*   Updated: 2024/08/18 18:28:59 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			i;
	unsigned char	*t;

	t = (unsigned char *)s;
	i = 0;
	while (i < len)
	{
		*t = (unsigned char)c;
		t++;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int N = 10;
// 	char a[N];
// 	ft_memset(a, '@', N);
// 	a[N - 1] = '\0';
// 	printf("%s\n", a);
// 	return (0);
// }
