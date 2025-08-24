/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xdup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:01:07 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/23 20:24:57 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_xdup2(int fildes, int fildes2)
{
	int fd;

	fd = dup2(fildes, fildes2);
	if (fd < 0)
		fatal_error("xdup2");
	return (fd);
}
