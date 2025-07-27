/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:09:50 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:14:45 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*t;

	p = *lst;
	while (p != NULL)
	{
		t = p;
		p = p -> next;
		ft_lstdelone(t, del);
	}
	*lst = NULL;
}

// #include <stdio.h>

// void del(void *p)
// {
//   free(p);
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

//   ft_lstclear(s, del);
//   return (0);
// }
