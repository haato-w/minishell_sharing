/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:14:16 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:53:03 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_xclose(int fd, t_context *g_ctx)
{
	if (fd < 0)
		return (-1);
	if (close(fd) < 0)
		fatal_error("xclose", g_ctx);
	return (0);
}
