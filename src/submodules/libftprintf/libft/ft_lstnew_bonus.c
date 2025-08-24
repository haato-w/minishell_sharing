/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:21:35 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:21:58 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = ft_calloc(sizeof(t_list), 1);
	if (ret == NULL)
		return (NULL);
	ret->content = content;
	ret->next = NULL;
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
//   t_list *t = ft_lstnew("abcdefg");
//   printf("%s\n", (char *)t->content);
//   printf("%p\n", t->next);
// }
