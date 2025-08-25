/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:59:22 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:54:30 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_node *node, t_context *g_ctx)
{
	if (node == NULL)
		return ;
	free_tok(node->args);
	free_tok(node->filename);
	free_tok(node->delimiter);
	if (2 < node->filefd)
		ft_xclose(node->filefd, g_ctx);
	if (2 < node->stashed_targetfd)
		ft_xclose(node->stashed_targetfd, g_ctx);
	free_node(node->redirects, g_ctx);
	free_node(node->next, g_ctx);
	free_node(node->command, g_ctx);
	free(node);
}

void	free_tok(t_token *tok)
{
	if (tok == NULL)
		return ;
	if (tok->word)
		free(tok->word);
	free_tok(tok->next);
	free(tok);
}

void	free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
