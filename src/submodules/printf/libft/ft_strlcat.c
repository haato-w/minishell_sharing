/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:25:14 by haatwata          #+#    #+#             */
/*   Updated: 2024/08/18 18:53:38 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	idx;
	size_t	len_dest;
	size_t	len_src;

	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize <= len_dest)
		return (dstsize + len_src);
	idx = 0;
	while (idx < dstsize - len_dest - 1 && src[idx])
	{
		dst[len_dest + idx] = src[idx];
		idx++;
	}
	dst[len_dest + idx] = '\0';
	return (len_dest + len_src);
}

// #include <stdio.h>
// int main(void)
// {
// 	char s1[15];
// 	s1[0] = 'h'; s1[1] = 'e'; s1[2] = 'l'; 
// 	s1[3] = 'l'; s1[4] = 'o'; s1[5] = '\0';
// 	char *s2 = " world";

// 	//printf("%u\n", ft_strlcat(s1, s2, 2));
// 	//printf("%u\n", ft_strlcat(s1, s2, 6));
// 	printf("%u\n", ft_strlcat(s1, s2, 10));
// 	//printf("%s\n", ft_strlcat(s1, s2));
// 	return (0);
// }
