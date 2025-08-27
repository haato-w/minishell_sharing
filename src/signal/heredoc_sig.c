/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:32:53 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/27 19:49:02 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_handler(int signum)
{
	// g_ctx.sig = signum;
	g_sig_status = signum;
	// g_ctx.readline_interrupted = true;
	*get_readline_interrupted() = true;
	// g_ctx.last_status = 130;
	*get_last_status() = 130;
}

void	setup_heredoc_sig(t_context *g_ctx)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction", g_ctx);
	ignore_sig(SIGQUIT, g_ctx);
}
