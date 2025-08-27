/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:07:30 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/27 20:09:37 by haatwata         ###   ########.fr       */
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
		if (map_unset((*get_ctx()).envmap, argv[i]) < 0)
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
