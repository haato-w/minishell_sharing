/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:03:29 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 23:40:54 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_numeric(char *s)
{
	if (*s == '\0')
		return (false);
	if (*s == '-' || *s == '+')
	{
		s++;
		if (*s == '\0')
			return (false);
		if (*s == '-' || *s == '+')
			return (false);
	}
	while (*s)
	{
		if (!isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

static bool is_in_range(char *s)
{
	bool	positive;

	positive = true;
	if (*s == '-')
	{
		positive = false;
		s++;
	}
	if (19 < ft_strlen(s))
		return (false);
	if (positive && 19 == ft_strlen(s) && 0 < ft_strncmp(s, "9223372036854775807", 19))
		return (false);
	if (!positive && 19 == ft_strlen(s) && 0 < ft_strncmp(s, "9223372036854775808", 19))
		return (false);
	return (true);
}

static void	numeric_error(char **argv, t_node *node, t_token *tok)
{
	ft_dprintf(2, "exit\n");
	ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", argv[1]);
	free_argv(argv);
	free_node(node);
	free_tok(tok);
	map_del(g_ctx.envmap);
	exit(2);
}

int	builtin_exit(char **argv, t_node *node, t_token *tok)
{
	long long	exit_code;

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
			numeric_error(argv, node, tok);
		errno = 0;
		exit_code = ft_atoll(argv[1]);
		if (errno == ERANGE)
			numeric_error(argv, node, tok);
		exit_code = ((exit_code % 256) + 256) % 256;
	}
	ft_dprintf(2, "exit\n");
	free_argv(argv);
	free_node(node);
	free_tok(tok);
	map_del(g_ctx.envmap);
	exit(exit_code);
}
