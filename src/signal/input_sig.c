/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:40:58 by heart             #+#    #+#             */
/*   Updated: 2025/08/10 17:36:53 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	input_handler(int signum)
{
	g_ctx.sig = signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_dprintf(STDERR_FILENO, "^C");
	rl_done = 1;
	g_ctx.last_status = 130;
}

void	setup_input_sig(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = input_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction");
	ignore_sig(SIGQUIT);
}
