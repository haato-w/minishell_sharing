/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 06:03:54 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 06:14:35 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void item_update(t_item *item, const char *value)
{
	free(item->value);
	if (value == NULL)
		item->value = NULL;
	else
		item->value = ft_xstrdup(value);
}

static void map_insert(t_map *map, const char *name, const char *value)
{
	t_item *item;

	if (value == NULL)
		item = item_new(ft_xstrdup(name), NULL, 0);
	else
		item = item_new(ft_strdup(name), ft_xstrdup(value), 0);
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

int map_set(t_map *map, const char *name, const char *value)
{
  t_item *cur;

  if (name == NULL || !is_identifier(name))
    return (-1);
  cur = map->item_head.next;
  while (cur)
  {
    if (strcmp(cur->name, name) == 0)
      break;
    cur = cur->next;
  }
  // found
  if (cur)
  {
    free(cur->value);
    if (value == NULL)
      cur->value = NULL;
    else
    {
      cur->value = strdup(value);
      if (cur->value == NULL)
        fatal_error("map_set strdup");
    }
  }
  // not found
  else
  {
    if (value == NULL)
    {
      cur = item_new(strdup(name), NULL);
      if (cur->name == NULL)
        fatal_error("strdup");
    }
    else
    {
      cur = item_new(strdup(name), strdup(value));
      if (cur->name == NULL || cur->value == NULL)
        fatal_error("strdup");
    }
    cur->next = map->item_head.next;
    map->item_head.next = cur;
  }
  return (0);
}
