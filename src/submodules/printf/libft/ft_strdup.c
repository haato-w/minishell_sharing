/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:48:24 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:49:12 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	ret = (char *)ft_calloc(s1_len + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
//   char s1[] = "hello";
//   printf("%s\n", s1);
//   printf("%s\n", ft_strdup(s1));
//   char s2[] = "";
//   printf("%s\n", s2);
//   printf("%s\n", ft_strdup(s2));
//   char s3[] = "aaa";
//   printf("%s\n", s3);
//   printf("%s\n", ft_strdup(s3));
//   char s4[] = "! !a2";
//   printf("%s\n", s4);
//   printf("%s\n", ft_strdup(s4));
// }
