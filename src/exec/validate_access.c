/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:26:04 by heart             #+#    #+#             */
/*   Updated: 2025/08/24 21:30:32 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void free_resources(char **argv, t_node *root_node, t_token *tok, t_context g_ctx)
{
	free_argv(argv);
	free_node(root_node, g_ctx);
	free_tok(tok);
}

void	validate_access(const char *path, char **argv,
	t_node *root_node, t_token *tok, t_context g_ctx)
{
	struct stat	st;
	const char *filename = argv[0];

	if (path == NULL)
	{
		char *tmp = ft_xstrdup(argv[0], g_ctx);
		free_resources(argv, root_node, tok, g_ctx);
		err_exit(tmp, "command not found", 127, g_ctx);
	}
	if (ft_strncmp(filename, "", 1) == 0)
	{
		char *tmp = ft_xstrdup(argv[0], g_ctx);
		free_resources(argv, root_node, tok, g_ctx);
		err_exit(tmp, "command not found", 127, g_ctx);
	}
	if (ft_strncmp(filename, "..", 3) == 0)
	{
		char *tmp = ft_xstrdup(argv[0], g_ctx);
		free_resources(argv, root_node, tok, g_ctx);
		err_exit(tmp, "command not found", 127, g_ctx);
	}
	if (access(path, F_OK) < 0)
	{
		char *tmp = ft_xstrdup(argv[0], g_ctx);
		free_resources(argv, root_node, tok, g_ctx);
		err_exit(tmp, "command not found", 127, g_ctx);
	}
	if (stat(path, &st) < 0)
	{
		free_resources(argv, root_node, tok, g_ctx);
		fatal_error("fstat", g_ctx);
	}
	if (S_ISDIR(st.st_mode))
	{
		char *tmp = ft_xstrdup(argv[0], g_ctx);
		free_resources(argv, root_node, tok, g_ctx);
		err_exit(tmp, "is a directory", 126, g_ctx);
	}
	if (access(path, X_OK) < 0)
	{
		char *tmp = ft_xstrdup(path, g_ctx);
		free_resources(argv, root_node, tok, g_ctx);
		err_exit(tmp, "Permission denied", 126, g_ctx);
	}
}
