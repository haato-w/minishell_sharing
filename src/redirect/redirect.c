/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:55:13 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:53:31 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool is_valid_fd(int fd)
{
	struct  stat st;
	
	if (fd < 0)
		return (false);
	errno = 0;
	if (fstat(fd, &st) < 0 && errno == EBADF)
		return (false);
	return (true);
}

int	stashfd(int fd, t_context *g_ctx)
{
	int	stashfd;

	if (!is_valid_fd(fd))
	{
		errno = EBADF;
		return (-1);
	}
	stashfd = 10;
	while (is_valid_fd(stashfd))
		stashfd++;
	stashfd = ft_xdup2(fd, stashfd, g_ctx);
	ft_xclose(fd, g_ctx);
	return (stashfd);
}

bool	in_redirect(t_node *node)
{
	if (node->kind == ND_REDIR_OUT)
		return (true);
	else if (node->kind == ND_REDIR_IN)
		return (true);
	else if (node->kind == ND_REDIR_APPEND)
		return (true);
	else if (node->kind == ND_REDIR_HEREDOC)
		return (true);
	return (false);
}

void	do_redirect(t_node *redir, t_context *g_ctx)
{
	if (redir == NULL)
		return ;
	if (in_redirect(redir))
	{
		redir->stashed_targetfd = stashfd(redir->targetfd, g_ctx);
		dup2(redir->filefd, redir->targetfd);
	}
	else
		assert_error("do_redirect", g_ctx);
	do_redirect(redir->next, g_ctx);
}

void	reset_redirect(t_node *redir, t_context *g_ctx)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next, g_ctx);
	if (in_redirect(redir))
	{
		ft_xdup2(redir->stashed_targetfd, redir->targetfd, g_ctx);
	}
	else
		assert_error("reset_redirect", g_ctx);
}
