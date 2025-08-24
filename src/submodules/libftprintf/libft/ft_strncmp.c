/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:59:09 by haatwata          #+#    #+#             */
/*   Updated: 2025/06/26 14:34:45 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	if (n == 0)
		return (0);
	idx = 0;
	while (idx < n && s1[idx] != '\0' && s2[idx] != '\0' && s1[idx] == s2[idx])
	{
		idx++;
	}
	if (idx == n)
		idx--;
	if (s1[idx] == s2[idx])
		return (0);
	else if ((unsigned char)s1[idx] > (unsigned char)s2[idx])
		return (1);
	else
		return (-1);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char *s1 = "abc";
// 	char *s2 = "abc";
// 	char *s3 = "def";
// 	char *s4 = "abd";
// 	char *s5 = "test";
// 	char *s6 = "teste";

// 	printf("%d\n", strncmp(s1, s3, 3));
// 	printf("%d\n", strncmp(s1, s2, 3));
// 	printf("%d\n", strncmp(s3, s1, 3)); 
// 	printf("%d\n", strncmp(s1, s4, 2));
// 	printf("%d\n", strncmp(s3, s1, 1));
// 	printf("%d\n", ft_strncmp(s5, s6, 10));
// }
