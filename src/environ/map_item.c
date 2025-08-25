/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:15:43 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:37:41 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_item	*item_new(char *name, char *value, int attributes, t_context *g_ctx)
{
	t_item	*item;

	item = ft_calloc(1, sizeof(*item));
	if (item == NULL)
		fatal_error("ft_calloc", g_ctx);
	item->name = name;
	item->value = value;
	item->attributes = attributes;
	return (item);
}

bool	item_exported(t_item *item)
{
	return (item->attributes & ATTR_EXPORT);
}

char	*item_get_string(t_item *item, t_context *g_ctx)
{
	size_t	strsize;
	char	*string;

	strsize = ft_strlen(item->name) + 2;
	if (item->value)
		strsize += ft_strlen(item->value);
	string = malloc(strsize);
	if (string == NULL)
		fatal_error("malloc", g_ctx);
	ft_strlcpy(string, item->name, strsize);
	if (item->value)
	{
		ft_strlcat(string, "=", strsize);
		ft_strlcat(string, item->value, strsize);
	}
	return (string);
}
