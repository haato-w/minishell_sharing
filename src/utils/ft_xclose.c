/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:14:16 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 21:09:21 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_xclose(int fd, t_context g_ctx)
{
	if (fd < 0)
		return (-1);
	if (close(fd) < 0)
		fatal_error("xclose", g_ctx);
	return (0);
}
