/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:32:53 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/27 20:11:14 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_handler(int signum)
{
	sig = signum;
	(*get_ctx()).readline_interrupted = true;
	(*get_ctx()).last_status = 130;
}

void	setup_heredoc_sig(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction");
	ignore_sig(SIGQUIT);
}
