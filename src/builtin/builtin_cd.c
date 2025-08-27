/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:10:32 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/27 20:29:23 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*resolve_pwd(char *oldpwd, char *path)
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
			append_path_elem(newpwd, PATH_MAX, &path, path);
	}
	dup = ft_strdup(newpwd);
	if (dup == NULL)
		fatal_error("strdup");
	return (dup);
}

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
	char	*pwd;
	char	path[PATH_MAX];
	char	*newpwd;

	pwd = xgetenv("PWD");
	update_oldpwd(pwd);
	if (set_path(path, PATH_MAX, argv[1]) < 0)
		return (1);
	if (chdir(path) < 0)
	{
		xperror3("cd", path, NULL);
		return (1);
	}
	newpwd = resolve_pwd(pwd, path);
	if (map_get((*get_ctx()).envmap, "PWD") != NULL)
		map_set((*get_ctx()).envmap, "PWD", newpwd);
	free(newpwd);
	return (0);
}
