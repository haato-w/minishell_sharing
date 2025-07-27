/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:29:22 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:29:33 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int main(void)
// {
//   ft_putchar_fd('a', STDOUT_FILENO);
//   ft_putchar_fd('\n', STDOUT_FILENO);
//   ft_putchar_fd(' ', STDOUT_FILENO);
//   ft_putchar_fd('\n', STDOUT_FILENO);
//   ft_putchar_fd('1', STDOUT_FILENO);
//   ft_putchar_fd('\n', STDOUT_FILENO);
// }
