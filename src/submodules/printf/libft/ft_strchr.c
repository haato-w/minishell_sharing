/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:47:02 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:47:58 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
//         char s1[] = "hello";
//         char c1 = 'h';
//         printf("%s\n", ft_strchr(s1, c1));
//         char s2[] = "hello";
//         char c2 = 'l';
//         printf("%s\n", ft_strchr(s2, c2));
//         char s3[] = "hello";
//         char c3 = 'a';
//         printf("%s\n", ft_strchr(s3, c3));
//         char s4[] = "";
//         char c4 = '1';
//         printf("%s\n", ft_strchr(s4, c4));
//         char s5[] = "hello";
//         char c5 = 'o';
//         printf("%s\n", ft_strchr(s5, c5));

// 		char s6[] = "teste";
//         printf("%s\n", ft_strchr(s6, 1024));
//         printf("%s\n", ft_strchr(s6, 1024));
// }
