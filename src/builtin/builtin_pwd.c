/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:05:04 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:57:24 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	equal_to_cwd(const char *path, t_context *g_ctx)
{
	struct stat	st1;
	struct stat	st2;

	memset(&st1, 0, sizeof(st1));
	memset(&st2, 0, sizeof(st2));
	if (stat(path, &st1) < 0)
		return (false);
	if (stat(".", &st2) < 0)
		fatal_error("stat", g_ctx);
	return (st1.st_ino == st2.st_ino);
}

int	builtin_pwd(char **argv, t_context *g_ctx)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd = xgetenv("PWD", g_ctx);
	if (pwd == NULL || !equal_to_cwd(pwd, g_ctx))
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			if (pwd != NULL)
			{
				ft_printf("%s\n", pwd);
				return (0);
			}
			xperror3("pwd", "getcwd", NULL);
			return (1);
		}
		ft_printf("%s\n", cwd);
	}
	else
		ft_printf("%s\n", pwd);
	return (0);
}
