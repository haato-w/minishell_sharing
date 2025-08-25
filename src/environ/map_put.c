/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:22:23 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:39:04 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_name_value(const char *string, char **name, char **value, t_context *g_ctx)
{
	char	*name_end;

	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		*name = ft_xstrdup(string, g_ctx);
		*value = NULL;
	}
	else
	{
		*name = ft_xstrndup(string, name_end - string, g_ctx);
		*value = ft_xstrdup(name_end + 1, g_ctx);
	}
}

int	map_put(t_map *map, const char *string, bool allow_empty_value, int attr, t_context *g_ctx)
{
	int		result;
	char	*name;
	char	*value;

	set_name_value(string, &name, &value, g_ctx);
	if (value == NULL && !allow_empty_value)
	{
		free(name);
		return (-1);
	}
	result = map_set_attr(map, name, value, attr, g_ctx);
	free(name);
	free(value);
	return (result);
}
