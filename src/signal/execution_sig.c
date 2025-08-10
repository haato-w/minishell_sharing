/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:34:12 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/10 17:34:42 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execution_handler(int signum)
{
	g_ctx.sig = signum;
	if (signum == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit (core dumped)");
	ft_dprintf(STDERR_FILENO, "\n");
	g_ctx.last_status = 130;
}

static void	setup_execution_sigint(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = execution_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction");
}

static void	setup_execution_sigquit(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = execution_handler;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	setup_execution_sig(void)
{
	setup_execution_sigint();
	setup_execution_sigquit();
}
