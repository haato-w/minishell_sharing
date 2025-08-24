/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:31:50 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 22:08:37 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*xgetenv(const char *name, t_context g_ctx)
{
	t_item	*item;

	item = map_get(g_ctx.envmap, name);
	if (item == NULL)
		return (NULL);
	return (item->value);
}

static void	envmap_init(t_map *map, char **ep, t_context *g_ctx)
{
	char	cwd[PATH_MAX];
	t_item	*tmp_item;
	char	*next_lvl;

	while (*ep)
	{
		map_put(map, *ep, false, ATTR_EXPORT, g_ctx);
		ep++;
	}
	tmp_item = map_get(map, "SHLVL");
	if (tmp_item == NULL)
		map_set_attr(map, "SHLVL", "1", ATTR_EXPORT, g_ctx);
	else
	{
		next_lvl = ft_itoa(ft_atoi(tmp_item->value) + 1);
		map_set_attr(map, "SHLVL", next_lvl, ATTR_EXPORT, g_ctx);
		free(next_lvl);
	}
	if (map_get(map, "PWD") == NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			xperror3("shell-init", "getcwd", NULL);
		else
			map_set_attr(map, "PWD", cwd, ATTR_EXPORT, g_ctx);
	}
	map_unset(map, "IFS");
	map_set_attr(map, "IFS", " \t\n", ATTR_EXPORT, g_ctx);
}

void	initenv(t_context *g_ctx)
{
	extern char	**environ;

	g_ctx->envmap = map_new(g_ctx);
	envmap_init(g_ctx->envmap, environ, g_ctx);
}

char	**get_environ(t_map *map, t_context g_ctx)
{
	size_t	i;
	size_t	size;
	t_item	*item;
	char	**environ;

	size = map_len(map, false) + 1;
	environ = ft_calloc(size, sizeof(char *));
	i = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value && item_exported(item))
		{
			environ[i] = item_get_string(item, g_ctx);
			i++;
		}
		item = item->next;
	}
	environ[i] = NULL;
	return (environ);
}
