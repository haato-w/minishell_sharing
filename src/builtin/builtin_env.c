/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:02:27 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 20:38:35 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char **argv, t_context g_ctx)
{
	t_item	*cur;

	(void)argv;
	cur = g_ctx.envmap->item_head.next;
	while (cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->name, cur->value);
		cur = cur->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}
