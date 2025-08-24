/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:06:59 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 21:19:11 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	item_update(t_item *item, const char *value, t_context g_ctx)
{
	free(item->value);
	if (value == NULL)
		item->value = NULL;
	else
		item->value = ft_xstrdup(value, g_ctx);
}

static void	map_insert(t_map *map, const char *name, const char *value, t_context g_ctx)
{
	t_item	*item;

	if (value == NULL)
		item = item_new(ft_xstrdup(name, g_ctx), NULL, 0, g_ctx);
	else
		item = item_new(ft_xstrdup(name, g_ctx), ft_xstrdup(value, g_ctx), 0, g_ctx);
	item->next = map->item_head.next;
	map->item_head.next = item;
}

int	map_set(t_map *map, const char *name, const char *value, t_context g_ctx)
{
	t_item	*item;

	if (name == NULL || !is_identifier(name))
		return (-1);
	item = map_get(map, name);
	if (item)
		item_update(item, value, g_ctx);
	else
		map_insert(map, name, value, g_ctx);
	return (0);
}

int	map_set_attr(t_map *map, const char *name, const char *value, int attr, t_context g_ctx)
{
	t_item	*item;

	if (map_set(map, name, value, g_ctx) < 0)
		return (-1);
	item = map_get(map, name);
	if (item == NULL)
		assert_error("map_set_attr", g_ctx);
	item->attributes = attr;
	return (0);
}
