/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:05:04 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/10 22:14:55 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool equal_to_cwd(const char *path)
{
	struct stat	st1;
	struct stat	st2;

	memset(&st1, 0, sizeof(st1));
	memset(&st2, 0, sizeof(st2));
	if (stat(path, &st1) < 0)
		return (false);
	if (stat(".", &st2) < 0)
		fatal_error("stat");
	return (st1.st_ino == st2.st_ino);
}

int	builtin_pwd(char **argv)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd = xgetenv("PWD");
	if (pwd == NULL || !equal_to_cwd(pwd))
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			xperror3("pwd", "getcwd", NULL);
			return (1);
		}
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
