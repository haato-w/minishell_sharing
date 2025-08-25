/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:32:53 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:51:53 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_handler(int signum)
{
	// g_ctx.sig = signum;
	g_sig_status = signum;
	// g_ctx.readline_interrupted = true;
	// g_ctx.last_status = 130;
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
