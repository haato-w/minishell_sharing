/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:05:26 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:58:06 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_pipe(int dst[2], int src[2]);

void	prepare_pipe(t_node *node, t_context *g_ctx)
{
	if (node->next == NULL)
		return ;
	if (pipe(node->outpipe) < 0)
		fatal_error("pipe", g_ctx);
	cpy_pipe(node->next->inpipe, node->outpipe);
}

void	prepare_pipe_child(t_node *node)
{
	if (0 <= node->outpipe[0])
		close(node->outpipe[0]);
	dup2(node->inpipe[0], STDIN_FILENO);
	if (node->inpipe[0] != STDIN_FILENO && 0 <= node->inpipe[0])
		close(node->inpipe[0]);
	dup2(node->outpipe[1], STDOUT_FILENO);
	if (node->outpipe[1] != STDOUT_FILENO && 0 <= node->outpipe[1])
		close(node->outpipe[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->inpipe[0] != STDIN_FILENO && 0 <= node->inpipe[0])
		close(node->inpipe[0]);
	if (node->next && 0 <= node->outpipe[1])
		close(node->outpipe[1]);
}

static void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}
