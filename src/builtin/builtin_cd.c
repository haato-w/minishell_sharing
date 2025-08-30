/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:10:32 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/30 14:27:31 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_oldpwd(char *pwd)
{
	if (pwd == NULL)
		map_set((*get_ctx()).envmap, "OLDPWD", "");
	else
		map_set((*get_ctx()).envmap, "OLDPWD", pwd);
}

static int	set_path(char *path, size_t path_size, char *arg)
{
	char	*home;

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

int	builtin_cd(char **argv)
{
	char	*env_pwd;
	char	pwd[PATH_MAX];
	char	path[PATH_MAX];

	env_pwd = xgetenv("PWD");
	update_oldpwd(env_pwd);
	if (set_path(path, PATH_MAX, argv[1]) < 0)
		return (1);
	if (chdir(path) < 0)
	{
		xperror3("cd", path, NULL);
		return (1);
	}
	if (getcwd(pwd, PATH_MAX) == NULL)
		fatal_error("getcwd");
	if (map_get((*get_ctx()).envmap, "PWD") != NULL)
		map_set((*get_ctx()).envmap, "PWD", pwd);
	return (0);
}
