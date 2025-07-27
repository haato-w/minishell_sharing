/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:01:34 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 19:03:05 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	g_m_size(char const *s, unsigned int st, size_t len, size_t s_l)
{
	size_t	alloc_len;

	s_l = ft_strlen(s);
	if (s_l < st)
		return (0);
	alloc_len = s_l - st;
	if (len < alloc_len)
		alloc_len = len;
	return (alloc_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	s_len;
	size_t	alloc_len;

	s_len = ft_strlen(s);
	alloc_len = g_m_size(s, start, len, s_len);
	ret = ft_calloc(sizeof(char), alloc_len + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < alloc_len)
	{
		ret[i] = s[start + i];
		i++;
	}
	if (s_len < start)
		ret[0] = '\0';
	else
		ret[start + i] = '\0';
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s1 = "hello";
// 	printf("%s\n", ft_substr(s1, 1, 3));
// 	char *s2 = "hola";
// 	printf("%s\n", ft_substr(s2, -1, 0));
// }
