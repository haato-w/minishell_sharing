/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:59:34 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 21:32:31 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(t_node *node)
{
	const char		*cmd_name;
	char const		*builtin_commands[] = {"exit", "export", "unset",
		"env", "cd", "echo", "pwd"};
	unsigned int	i;

	if (node == NULL || node->command == NULL
		|| node->command->args == NULL || node->command->args->word == NULL)
		return (false);
	cmd_name = node->command->args->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (ft_strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_node *node, t_token *tok, t_context g_ctx)
{
	int		status;
	char	**argv;

	do_redirect(node->command->redirects, g_ctx);
	argv = token_list_to_argv(node->command->args, g_ctx);
	if (ft_strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv, node, tok, g_ctx);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(argv, g_ctx);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(argv, g_ctx);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(argv, g_ctx);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = builtin_cd(argv, g_ctx);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = builtin_echo(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = builtin_pwd(argv, g_ctx);
	else
		todo("exec_builtin", g_ctx);
	free_argv(argv);
	reset_redirect(node->command->redirects, g_ctx);
	return (status);
}
