/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:22:23 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/09 20:54:23 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_name_value(const char *string, char **name, char **value)
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

int	map_put(t_map *map, const char *string, bool allow_empty_value, int attr)
{
	int		result;
	char	*name;
	char	*value;

	set_name_value(string, &name, &value);
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
