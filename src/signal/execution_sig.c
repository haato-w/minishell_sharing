/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:34:12 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/26 00:41:07 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execution_handler(int signum)
{
	// g_ctx.sig = signum;
	g_sig_status = signum;
	if (signum == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit (core dumped)");
	ft_dprintf(STDERR_FILENO, "\n");
	// g_ctx.last_status = 130;
}

static void	setup_execution_sigint(t_context *g_ctx)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = execution_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction", g_ctx);
}

static void	setup_execution_sigquit(t_context *g_ctx)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = execution_handler;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		fatal_error("sigaction", g_ctx);
}

void	setup_execution_sig(t_context *g_ctx)
{
	setup_execution_sigint(g_ctx);
	setup_execution_sigquit(g_ctx);
}
