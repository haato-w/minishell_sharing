/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:49:30 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:50:24 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	i = 0;
	while (i < s_len)
	{
		f(i, s + i);
		i++;
	}
}

// void f(unsigned int idx, char *s)
// {
//   if (idx % 2 == 1)
//     s[idx] = ' ';
// }

// #include <stdio.h>
// int main(void)
// {
//   char s1[] = "aaaaaaa";
//   ft_striteri(s1, f);
//   printf("%s\n", s1);
//   char s2[] = "abcdefg";
//   ft_striteri(s2, f);
//   printf("%s\n", s2);
//   char s3[] = "";
//   ft_striteri(s3, f);
//   printf("%s\n", s3);
//   char s4[] = "a";
//   ft_striteri(s4, f);
//   printf("%s\n", s4);
// }
