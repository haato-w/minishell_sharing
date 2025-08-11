/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesasaki <mesasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:10:32 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/11 17:47:41 by mesasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void update_oldpwd(char *pwd)
{
	if (pwd == NULL)
		map_set(g_ctx.envmap, "OLDPWD", "");
	else
		map_set(g_ctx.envmap, "OLDPWD", pwd);
}

static int set_path(char *path, size_t path_size, char *arg)
{
	char *home;

	if (arg == NULL)
	{
		home = xgetenv("HOME");
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

int builtin_cd(char **argv)
{
	char *pwd;
	char path[PATH_MAX];
	char newpwd[PATH_MAX];

	pwd = xgetenv("PWD");
	update_oldpwd(pwd);
	if (set_path(path, PATH_MAX, argv[1]) < 0)
		return (1);
	if (chdir(path) < 0)
	{
		xperror3("cd", path, NULL);
		return (1);
	}
	if (getcwd(newpwd, PATH_MAX) == NULL)
	{
		xperror3("cd", "getcwd", NULL);
		return (0);
	}
	map_set(g_ctx.envmap, "PWD", newpwd);
	return (0);
}
