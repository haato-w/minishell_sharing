/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:54:59 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:55:51 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	size_t	i;
	char	*ret;

	s_len = ft_strlen(s);
	ret = ft_calloc(sizeof(char), s_len + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	return (ret);
}

// char f(unsigned int idx, char c)
// {
//   if (idx % 2 == 1)
//     return (' ');
//   return (c);
// }

// #include <stdio.h>
// int main(void)
// {
//   printf("%s\n", ft_strmapi("aaaaaaa", f));
//   printf("%s\n", ft_strmapi("abcdefg", f));
//   printf("%s\n", ft_strmapi("", f));
//   printf("%s\n", ft_strmapi("a", f));
// }
