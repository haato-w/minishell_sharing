/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:29:52 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:30:03 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// int main(void)
// {
//   ft_putendl_fd("abc", STDOUT_FILENO);
//   ft_putendl_fd("a   a", STDOUT_FILENO);
//   ft_putendl_fd("12342", STDOUT_FILENO);
// }
