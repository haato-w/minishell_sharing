/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:29:53 by heart             #+#    #+#             */
/*   Updated: 2025/08/30 15:03:09 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_path(char *path, size_t pathsize, const char *filename,
			char **envpath)
{
	size_t	len;
	char	buf[PATH_MAX];
	char	*end;

	ft_bzero(path, pathsize);
	end = ft_strchr(*envpath, ':');
	if (*envpath == end)
		len = ft_strlcpy(path, ".", pathsize);
	else if (end)
	{
		len = ft_strlcpy(buf, *envpath, end - *envpath + 1);
		ft_strlcpy(path, buf, pathsize);
	}
	else
		len = ft_strlcpy(path, *envpath, pathsize);
	len += ft_strlcat(path, "/", pathsize);
	len += ft_strlcat(path, filename, pathsize);
	if (len > pathsize - 1)
		path[0] = '\0';
	if (end == NULL)
		*envpath = NULL;
	else
		*envpath = end + 1;
}

static char	*search_path_mode(const char *filename, int mode)
{
	char	path[PATH_MAX];
	char	*envpath;
	char	*dup;
	char	*tmp_path;

	envpath = xgetenv("PATH");
	while (envpath && *envpath)
	{
		set_path(path, PATH_MAX, filename, &envpath);
		if (access(path, mode) == 0)
		{
			dup = ft_strdup(path);
			return (dup);
		}
	}
	tmp_path = ft_strjoin("./", filename);
	if (access(tmp_path, mode) == 0)
		return (tmp_path);
	free(tmp_path);
	return (NULL);
}

char	*search_path(const char *filename)
{
	char	*path;

	path = search_path_mode(filename, X_OK);
	if (path)
		return (path);
	path = search_path_mode(filename, F_OK);
	return (path);
}
