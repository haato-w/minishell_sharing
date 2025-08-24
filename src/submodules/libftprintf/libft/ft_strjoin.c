/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:50:41 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:51:53 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = ft_calloc(sizeof(char), (s1_len + s2_len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		ret[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		ret[s1_len + i] = s2[i];
		i++;
	}
	ret[s1_len + s2_len] = '\0';
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s1 = "hello";
//   char *s2 = "world";
// 	printf("%s\n", ft_strjoin(s1, s2));
// }
