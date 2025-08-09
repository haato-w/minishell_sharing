/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:07:30 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/09 16:07:43 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(char **argv)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_unset(g_ctx.envmap, argv[i]) < 0)
		{
			builtin_error("unset", argv[i], "not a valid indentifier");
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	return (status);
}
