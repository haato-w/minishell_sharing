/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:03:29 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/09 22:27:41 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_numeric(char *s)
{
	if (*s == '\0')
		return (0);
	if (*s == '-' || *s == '+')
	{
		s++;
		if (*s == '\0')
			return (0);
		if (*s == '-' || *s == '+')
			return (0);
	}
	while (*s)
	{
		if (!isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	builtin_exit(char **argv)
{
	int	exit_code;

	exit_code = g_ctx.last_status;
	if (g_ctx.syntax_error)
	{
		xperror("syntax error\n");
		return (1);
	}
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
		{
			xperror("exit: too many arguments\n");
			exit(1);
		}
		if (!is_numeric(argv[1]))
		{
			builtin_error("exit: ", argv[1], ": numeric argument required\n");
			exit(2);
		}
		exit_code = atoi(argv[1]);
		exit_code = ((exit_code % 256) + 256) % 256;
	}
	dprintf(2, "exit\n");
	exit(exit_code);
}
