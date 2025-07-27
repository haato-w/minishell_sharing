/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:18:50 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:21:02 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*p;
	t_list	*t;

	start = ft_lstnew(f(lst -> content));
	if (start == NULL)
		return (start);
	p = lst -> next;
	while (p != NULL)
	{
		t = ft_lstnew(f(p -> content));
		if (t == NULL)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, t);
		p = p -> next;
	}
	return (start);
}

// #include <stdio.h>

// void del(void *p)
// {
//   free(p);
// }

// void *f(void *p)
// {
//   char *t = p;
//   *t = '0';
//   return (t);
// }

// int main(void)
// {
//   char *p = ft_calloc(1, sizeof(char));
//   *p = '1';
//   t_list *n1 = ft_lstnew(p);

//   t_list **s = ft_calloc(sizeof(t_list *), 1);
//   *s = n1;

//   p = ft_calloc(1, sizeof(char));
//   *p = '2';
//   t_list *n2 = ft_lstnew(p);

//   ft_lstadd_front(s, n2);

//   t_list *t = *s;
//   while (t != NULL)
//   {
//     printf("%s\n", (char *)t->content);
//     t = t -> next;
//   }

//   t_list *t2 = ft_lstmap(*s, f, del);

//   printf("===\n");
//   t = t2;
//   while (t != NULL)
//   {
//     printf("%s\n", (char *)t->content);
//     t = t -> next;
//   }
//   return (0);
// }
