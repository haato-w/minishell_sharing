/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:10:32 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 22:05:19 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*resolve_pwd(char *oldpwd, char *path, t_context g_ctx)
{
	char	newpwd[PATH_MAX];
	char	*dup;

	if (*path == '/' || oldpwd == NULL)
		ft_strlcpy(newpwd, "/", PATH_MAX);
	else
		ft_strlcpy(newpwd, oldpwd, PATH_MAX);
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (consume_path(&path, path, "."))
			;
		else if (consume_path(&path, path, ".."))
			delete_last_elem(newpwd);
		else
			append_path_elem(newpwd, PATH_MAX, &path, path, g_ctx);
	}
	dup = ft_strdup(newpwd);
	if (dup == NULL)
		fatal_error("strdup", g_ctx);
	return (dup);
}

static void	update_oldpwd(char *pwd, t_context g_ctx)
{
	if (pwd == NULL)
		map_set(g_ctx.envmap, "OLDPWD", "", g_ctx);
	else
		map_set(g_ctx.envmap, "OLDPWD", pwd, g_ctx);
}

static int	set_path(char *path, size_t path_size, char *arg, t_context g_ctx)
{
	char	*home;

	if (arg == NULL)
	{
		home = xgetenv("HOME", g_ctx);
		if (home == NULL)
		{
			xperror2("cd", "HOME not set");
			return (-1);
		}
		ft_strlcpy(path, home, path_size);
	}
	else
		ft_strlcpy(path, arg, path_size);
	return (0);
}

int	builtin_cd(char **argv, t_context g_ctx)
{
	char	*pwd;
	char	path[PATH_MAX];
	char	*newpwd;

	pwd = xgetenv("PWD", g_ctx);
	update_oldpwd(pwd, g_ctx);
	if (set_path(path, PATH_MAX, argv[1], g_ctx) < 0)
		return (1);
	if (chdir(path) < 0)
	{
		xperror3("cd", path, NULL);
		return (1);
	}
	newpwd = resolve_pwd(pwd, path, g_ctx);
	map_set(g_ctx.envmap, "PWD", newpwd, g_ctx);
	free(newpwd);
	return (0);
}
