/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:06:59 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/09 19:15:07 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	item_update(t_item *item, const char *value)
{
	free(item->value);
	if (value == NULL)
		item->value = NULL;
	else
		item->value = ft_xstrdup(value);
}

static void	map_insert(t_map *map, const char *name, const char *value)
{
	t_item	*item;

	if (value == NULL)
		item = item_new(ft_xstrdup(name), NULL, 0);
	else
		item = item_new(ft_xstrdup(name), ft_xstrdup(value), 0);
	item->next = map->item_head.next;
	map->item_head.next = item;
}

int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*item;

	if (name == NULL || !is_identifier(name))
		return (-1);
	item = map_get(map, name);
	if (item)
		item_update(item, value);
	else
		map_insert(map, name, value);
	return (0);
}

int	map_set_attr(t_map *map, const char *name, const char *value, int attr)
{
	t_item	*item;

	if (map_set(map, name, value) < 0)
		return (-1);
	item = map_get(map, name);
	if (item == NULL)
		assert_error("map_set_attr");
	item->attributes = attr;
	return (0);
}
