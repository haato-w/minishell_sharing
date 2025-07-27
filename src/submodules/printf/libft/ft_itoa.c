/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:04:03 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:06:47 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_n_length(int n)
{
	int	res_len;
	int	t;

	if (n == 0)
		return (1);
	t = n;
	res_len = 0;
	if (n < 0)
		res_len += 1;
	while (t != 0)
	{
		res_len += 1;
		t /= 10;
	}
	return (res_len);
}

static	char	*make_res_arr(int n, int n_len, char *ret_arr)
{
	long	t;
	int		i;

	t = n;
	if (t < 0)
		t *= -1;
	i = 0;
	while (t != 0)
	{
		ret_arr[n_len - i - 1] = '0' + (t % 10);
		t /= 10;
		i++;
	}
	if (n < 0)
		ret_arr[0] = '-';
	return (ret_arr);
}

char	*ft_itoa(int n)
{
	int		n_len;
	char	*ret;

	n_len = count_n_length(n);
	ret = ft_calloc(sizeof(char), n_len + 1);
	if (ret == NULL)
		return (NULL);
	ret[n_len] = '\0';
	if (n == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	make_res_arr(n, n_len, ret);
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	int i1 = 1234;
//   printf("i1: %d\n", i1);
//   printf("%s\n", ft_itoa(i1));
//   int i2 = -1234;
//   printf("i2: %d\n", i2);
//   printf("%s\n", ft_itoa(i2));
//   int i3 = 0;
//   printf("i3: %d\n", i3);
//   printf("%s\n", ft_itoa(i3));
//   int i4 = INT_MAX;
//   printf("INT_MAX: %d\n", INT_MAX);
//   printf("%s\n", ft_itoa(i4));
//   int i5 = INT_MIN;
//   printf("INT_MIN: %d\n", INT_MIN);
//   printf("%s\n", ft_itoa(i5));
//   int i6 = 1;
//   printf("1: %d\n", i6);
//   printf("%s\n", ft_itoa(i6));
//   int i7 = -1;
//   printf("-1: %d\n", i7);
//   printf("%s\n", ft_itoa(i7));
// }
