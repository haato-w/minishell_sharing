/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xdup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:01:07 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:52:49 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_xdup2(int fildes, int fildes2, t_context *g_ctx)
{
	int fd;

	fd = dup2(fildes, fildes2);
	if (fd < 0)
		fatal_error("xdup2", g_ctx);
	return (fd);
}
