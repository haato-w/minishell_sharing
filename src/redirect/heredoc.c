/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:52:46 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/24 21:13:15 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	readline_heredoc_loop(int pfd[2], const char *delimiter,
	bool is_delim_unquoted, t_context g_ctx)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_ctx.readline_interrupted || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (is_delim_unquoted)
			line = expand_heredoc_line(line, g_ctx);
		ft_dprintf(pfd[1], "%s\n", line);
		free(line);
	}
}

int	read_heredoc(const char *delimiter, bool is_delim_unquoted, t_context g_ctx)
{
	int		pfd[2];

	setup_sig_event_hook_heredoc();
	setup_heredoc_sig(g_ctx);
	if (pipe(pfd) < 0)
		fatal_error("pipe", g_ctx);
	g_ctx.readline_interrupted = false;
	readline_heredoc_loop(pfd, delimiter, is_delim_unquoted, g_ctx);
	close(pfd[1]);
	if (g_ctx.readline_interrupted)
	{
		close(pfd[0]);
		setup_sig_event_hook();
		return (-1);
	}
	setup_sig_event_hook();
	return (pfd[0]);
}
