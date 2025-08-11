/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:29:26 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/11 21:02:56 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

t_map	*map_new(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(*map));
	if (map == NULL)
		fatal_error("calloc");
	return (map);
}

void	map_del(t_map *map)
{
	t_item	*tmp_item;
	t_item	*tmp_item2;
	
	tmp_item = map->item_head.next;
	while (tmp_item != NULL)
	{
		free(tmp_item->name);
		free(tmp_item->value);
		tmp_item2 = tmp_item; 
		tmp_item = tmp_item->next;
		free(tmp_item2);
	}
	free(map);
}

t_item	*map_get(t_map *map, const char *name)
{
	t_item	*cur;

	if (name == NULL)
		return (NULL);
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

size_t	map_len(t_map *map, bool const_null_value)
{
	size_t	len;
	t_item	*item;

	len = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value || const_null_value)
			len++;
		item = item->next;
	}
	return (len);
}
