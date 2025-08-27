/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:26:04 by heart             #+#    #+#             */
/*   Updated: 2025/08/27 21:01:57 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_resources(char **argv, t_node *root_node, t_token *tok)
{
	free_argv(argv);
	free_node(root_node);
	free_tok(tok);
}

static void	cmd_validation(const char *path, char **argv,
	t_node *root_node, t_token *tok)
{
	const char	*filename;
	char		*tmp;

	filename = argv[0];
	if (path == NULL || ft_strncmp(filename, "", 1) == 0
		|| ft_strncmp(filename, "..", 3) == 0 || access(path, F_OK) < 0)
	{
		tmp = ft_xstrdup(argv[0]);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "command not found", 127);
	}
}

void	validate_access(const char *path, char **argv,
	t_node *root_node, t_token *tok)
{
	struct stat	st;
	char		*tmp;

	cmd_validation(path, argv, root_node, tok);
	if (stat(path, &st) < 0)
	{
		free_resources(argv, root_node, tok);
		fatal_error("fstat");
	}
	if (S_ISDIR(st.st_mode))
	{
		tmp = ft_xstrdup(argv[0]);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "is a directory", 126);
	}
	if (access(path, X_OK) < 0)
	{
		tmp = ft_xstrdup(path);
		free_resources(argv, root_node, tok);
		err_exit(tmp, "Permission denied", 126);
	}
}
