/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:15:20 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:15:37 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

// void del(void *p)
// {
//   free(p);
// }

// int main(void)
// {
//   char *p = ft_calloc(1, sizeof(char));
//   *p = '1';
//   t_list *n = ft_lstnew(p);
//   ft_lstdelone(n, del);
//   return (0);
// }
