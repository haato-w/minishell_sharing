/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:43:59 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 06:06:14 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static void	get_name(const char *string, char **name, char **value)
{
	char	*name_end;

	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		*name = ft_xstrdup(string);
		*value = NULL;
	}
	else
	{
		*name = ft_xstrndup(string, name_end - string);
		*value = ft_xstrdup(name_end + 1);
	}
}

int map_put(t_map *map, const char *string, bool allow_empty_value, int attr)
{
	int		result;
	char	*name;
	char	*value;

	get_name(string, &name, &value);
	if (value == NULL && !allow_empty_value)
	{
		free(name);
		return (-1);
	}
	result = map_set_attr(map, name, value, attr);
	free(name);
	free(value);
	return (result);
}
