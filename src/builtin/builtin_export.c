/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:04:06 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 22:02:00 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_allenv(t_context g_ctx)
{
	t_item	*cur;

	cur = g_ctx.envmap->item_head.next;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->name, cur->value);
		else
			printf("declare -x %s\n", cur->name);
		cur = cur->next;
	}
}

int	builtin_export(char **argv, t_context g_ctx)
{
	size_t	i;
	int		status;

	if (argv[1] == NULL)
	{
		print_allenv(g_ctx);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(g_ctx.envmap, argv[i], true, ATTR_EXPORT, g_ctx) < 0)
		{
			xperror_invalid_identifier("export", argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
