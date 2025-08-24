/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:55:13 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 15:33:09 by haatwata         ###   ########.fr       */
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

int	stashfd(int fd)
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
	stashfd = ft_xdup2(fd, stashfd);
	ft_xclose(fd);
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

void	do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (in_redirect(redir))
	{
		redir->stashed_targetfd = stashfd(redir->targetfd);
		dup2(redir->filefd, redir->targetfd);
	}
	else
		assert_error("do_redirect");
	do_redirect(redir->next);
}

void	reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next);
	if (in_redirect(redir))
	{
		ft_xclose(redir->filefd);
		ft_xclose(redir->targetfd);
		ft_xdup2(redir->stashed_targetfd, redir->targetfd);
	}
	else
		assert_error("reset_redirect");
}
