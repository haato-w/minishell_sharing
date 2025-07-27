/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:07:33 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:08:23 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*t;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		t = ft_lstlast(*lst);
		t -> next = new;
	}
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

//   n = ft_lstnew("3");
//   show_lst(n);
//   printf("\n");

//   ft_lstadd_back(s, n);

//   t_list *t;
//   t = *s;
//   printf("---\n");
//   while (t != NULL) {
//     show_lst(t);
//     printf("\n");
//     t = t -> next;
//   }

//   printf("%d\n", ft_lstsize(*s));
// }
