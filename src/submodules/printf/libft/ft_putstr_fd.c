/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:31:21 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:31:33 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	write(fd, s, s_len);
}

// int main(void)
// {
//   ft_putstr_fd("abc", STDOUT_FILENO);
//   ft_putstr_fd("\n", STDOUT_FILENO);
//   ft_putstr_fd("a   a", STDOUT_FILENO);
//   ft_putstr_fd("\n", STDOUT_FILENO);
//   ft_putstr_fd("12342", STDOUT_FILENO);
//   ft_putstr_fd("\n", STDOUT_FILENO);
// }
