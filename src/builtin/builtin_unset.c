/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:07:30 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:55:35 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(char **argv, t_context *g_ctx)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_unset(g_ctx->envmap, argv[i]) < 0)
		{
			xperror_invalid_identifier("unset", argv[i]);
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	return (status);
}
