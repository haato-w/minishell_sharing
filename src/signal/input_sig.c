/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:40:58 by heart             #+#    #+#             */
/*   Updated: 2025/08/27 19:20:53 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	input_handler(int signum)
{
	// g_ctx.sig = signum;
	g_sig_status = signum;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// g_ctx.last_status = 130;
}

void	setup_input_sig(t_context *g_ctx)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = input_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction", g_ctx);
	ignore_sig(SIGQUIT, g_ctx);
}
