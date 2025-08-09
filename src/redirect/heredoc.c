/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:52:46 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/09 18:53:24 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	readline_heredoc_loop(int pfd[2], const char *delimiter,
	bool is_delim_unquoted)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_ctx.readline_interrupted || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (is_delim_unquoted)
			line = expand_heredoc_line(line);
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
}

int	read_heredoc(const char *delimiter, bool is_delim_unquoted)
{
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	g_ctx.readline_interrupted = false;
	readline_heredoc_loop(pfd, delimiter, is_delim_unquoted);
	close(pfd[1]);
	if (g_ctx.readline_interrupted)
	{
		close(pfd[0]);
		return (-1);
	}
	return (pfd[0]);
}
