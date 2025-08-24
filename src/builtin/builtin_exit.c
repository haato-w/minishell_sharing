/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:03:29 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 16:31:15 by haatwata         ###   ########.fr       */
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

int	builtin_exit(char **argv, t_node *node, t_token *tok)
{
	int	exit_code;

	exit_code = g_ctx.last_status;
	if (g_ctx.syntax_error)
	{
		ft_dprintf(2, "minishell: syntax error\n");
		return (1);
	}
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
		{
			ft_dprintf(2, "exit\n");
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		if (!is_numeric(argv[1]))
		{
			ft_dprintf(2, "exit\n");
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", argv[1]);
			free_node(node);
			free_tok(tok);
			map_del(g_ctx.envmap);
			exit(2);
		}
		exit_code = ft_atoi(argv[1]);
		exit_code = ((exit_code % 256) + 256) % 256;
	}
	ft_dprintf(2, "exit\n");
	free_argv(argv);
	free_node(node);
	free_tok(tok);
	map_del(g_ctx.envmap);
	exit(exit_code);
}
