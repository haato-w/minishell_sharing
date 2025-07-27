/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:59:47 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 19:01:17 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trim_dup(char const *s, size_t len)
{
	char	*ret;
	size_t	idx;

	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		ret[idx] = s[idx];
		idx++;
	}
	ret[len] = '\0';
	return (ret);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	idx;
	size_t	start;
	size_t	s_len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	s_len = ft_strlen(s1);
	if (s_len == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	idx = 0;
	while (idx < s_len && ft_strchr(set, s1[idx]))
		idx++;
	start = idx;
	idx = s_len - 1;
	while (start < idx && ft_strchr(set, s1[idx]))
		idx--;
	if (start == idx && !s1[start])
		return ((char *)ft_calloc(1, sizeof(char)));
	return (trim_dup(s1 + start, idx - start + 1));
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s1 = "abcdefghijklmn";
// 	char *set1 = "lmabckn";
// 		printf("%s\n", ft_strtrim(s1, set1));
// 	char *s2 = "abcdefghijklmn";
// 	char *set2 = "";
// 	printf("%s\n", ft_strtrim(s2, set2));
// 	char *s3 = "";
// 	char *set3 = "lmabckn";
// 	printf("%s\n", ft_strtrim(s3, set3));
// 	char *s4 = "";
// 	char *set4 = "";
// 	printf("%s\n", ft_strtrim(s4, set4));
// 	char *s5 = "hello";
// 	char *set5 = "hello";
// 	printf("%s\n", ft_strtrim(s5, set5));

// 	char *s6 = "   xxxtripouille";
// 	char *set6 = " x";
// 	printf("%s\n", ft_strtrim(s6, set6));

// 	char *s7 = "tripouille   xxx";
// 	char *set7 = " x";
// 	printf("%s\n", ft_strtrim(s7, set7));
// }
