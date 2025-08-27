/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:03:29 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/27 20:54:42 by haatwata         ###   ########.fr       */
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

static void	free_resources(char **argv, t_node *node, t_token *tok)
{
	free_argv(argv);
	free_node(node);
	free_tok(tok);
	map_del((*get_ctx()).envmap);
}

static void	numeric_error(char **argv, t_node *node, t_token *tok)
{
	ft_dprintf(2, "exit\n");
	ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", argv[1]);
	free_resources(argv, node, tok);
	exit(2);
}

static long long	get_exit_code(char **argv, t_node *node, t_token *tok)
{
	long long	exit_code;

	if (!is_numeric(argv[1]))
		numeric_error(argv, node, tok);
	errno = 0;
	exit_code = ft_atoll(argv[1]);
	if (errno == ERANGE)
		numeric_error(argv, node, tok);
	exit_code = ((exit_code % 256) + 256) % 256;
	return (exit_code);
}

int	builtin_exit(char **argv, t_node *node, t_token *tok)
{
	long long	exit_code;

	exit_code = (*get_ctx()).last_status;
	if ((*get_ctx()).syntax_error)
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
		exit_code = get_exit_code(argv, node, tok);
	}
	ft_dprintf(2, "exit\n");
	free_resources(argv, node, tok);
	exit(exit_code);
}
