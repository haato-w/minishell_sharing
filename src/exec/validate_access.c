/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:26:04 by heart             #+#    #+#             */
/*   Updated: 2025/08/24 17:09:37 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void free_resources(char **argv, t_node *root_node, t_token *tok)
{
	free_argv(argv);
	free_node(root_node);
	free_tok(tok);
}

void	validate_access(const char *path, char **argv,
	t_node *root_node, t_token *tok)
{
	struct stat	st;
	const char *filename = argv[0];

	if (path == NULL)
	{
		char *tmp = ft_xstrdup(argv[0]);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "command not found", 127);
	}
	if (ft_strncmp(filename, "", 1) == 0)
	{
		char *tmp = ft_xstrdup(argv[0]);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "command not found", 127);
	}
	if (ft_strncmp(filename, "..", 3) == 0)
	{
		char *tmp = ft_xstrdup(argv[0]);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "command not found", 127);
	}
	if (access(path, F_OK) < 0)
	{
		char *tmp = ft_xstrdup(argv[0]);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "command not found", 127);
	}
	if (stat(path, &st) < 0)
	{
		free_resources(argv, root_node, tok);
		fatal_error("fstat");
	}
	if (S_ISDIR(st.st_mode))
	{
		char *tmp = ft_xstrdup(argv[0]);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "is a directory", 126);
	}
	if (access(path, X_OK) < 0)
	{
		char *tmp = ft_xstrdup(path);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "Permission denied", 126);
	}
}
