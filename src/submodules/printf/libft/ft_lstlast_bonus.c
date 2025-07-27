/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:17:26 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:18:04 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*t;

	t = lst;
	if (t == NULL)
		return (NULL);
	while (t->next != NULL)
	{
		t = t->next;
	}
	return (t);
}

// #include <stdio.h>
// void show_lst(t_list *n)
// {
//   printf("n: %p\n", n);
//   printf("content: %s\n", (char *)n->content);
//   printf("next: %p\n", n->next);
// }

// int main(void)
// {
//   t_list *n = ft_lstnew("1");
//   show_lst(n);
//   printf("\n");
//   t_list **s = ft_calloc(sizeof(t_list *), 1);
//   *s = n;

//   n = ft_lstnew("2");
//   show_lst(n);
//   printf("\n");

//   printf("*s: %p\n\n", *s);

//   ft_lstadd_front(s, n);
//   printf("*s: %p\n\n", *s);

//   t_list *t;
//   t = *s;
//   while (t != NULL) {
//     show_lst(t);
//     printf("\n");
//     t = t -> next;
//   }

//   printf("%s\n", (char *)ft_lstlast(*s) -> content);
// }
