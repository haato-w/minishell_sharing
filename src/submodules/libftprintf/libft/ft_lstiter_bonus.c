/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:16:08 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:16:55 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*p;

	p = lst;
	while (p != NULL)
	{
		f(p -> content);
		p = p -> next;
	}
}

// #include <stdio.h>

// void f(void *p)
// {
//   char *t = p;
//   *t = '0';
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

//   ft_lstiter(*s, f);

//   printf("===\n");
//   t = *s;
//   while (t != NULL)
//   {
//     printf("%s\n", (char *)t->content);
//     t = t -> next;
//   }
//   return (0);
// }
