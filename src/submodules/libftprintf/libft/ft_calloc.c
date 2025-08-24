/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:54:03 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:00:09 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_valid(size_t count, size_t size)
{
	if (count > SIZE_MAX / size)
		return (false);
	return (true);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret;

	if (count != 0 && size != 0 && !is_valid(count, size))
		return (NULL);
	ret = (unsigned char *)malloc(size * count);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, size * count);
	return ((void *)ret);
}

// #include <stdio.h>
// #include <stdlib.h>
// void show(void *p, int b)
// {
//   int i = 0;

//   unsigned char *t = p;
//   while (i < b)
//   {
//     if (t[i] == 0)
//       printf("0");
//     i++;
//   }
//   printf("\n");
// }

// int main(void)
// {
// //   int size = 1;
// //   int count = 1;
// //   show(ft_calloc(count, size), size * count);
// //   size = 2;
// //   count = 2;
// //   show(ft_calloc(count, size), size * count);
// //   size = 0;
// //   count = 10;
// //   show(ft_calloc(count, size), size * count);
// //   show(calloc(count, size), size * count);

// 	if (calloc(SIZE_MAX, 3) == NULL)
// 		printf("Yes\n");
// 	else
// 		printf("No\n");

// }
