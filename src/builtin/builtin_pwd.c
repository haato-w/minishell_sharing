/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesasaki <mesasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:05:04 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/11 17:25:22 by mesasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_pwd(char **argv)
{
	char *pwd;
	char cwd[PATH_MAX];

	(void)argv;
	pwd = xgetenv("PWD");
	if (pwd != NULL && *pwd != '\0') // PWDが存在し、空文字列でない場合
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		xperror3("pwd", "getcwd", NULL);
		return (1);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
