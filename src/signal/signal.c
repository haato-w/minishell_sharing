/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:42:59 by heart             #+#    #+#             */
/*   Updated: 2025/08/27 20:20:08 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_state_heredoc(void)
{
	if (sig == 0)
		return (0);
	else if (sig == SIGINT)
	{
		sig = 0;
		rl_done = 1;
		(*get_ctx()).last_status = 130;
		return (0);
	}
	return (0);
}

static int	check_state(void)
{
	if (sig == 0)
		return (0);
	else if (sig == SIGINT)
	{
		sig = 0;
		(*get_ctx()).last_status = 130;
		return (0);
	}
	return (0);
}

void	setup_sig_event_hook_heredoc(void)
{
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state_heredoc;
}

void	setup_sig_event_hook(void)
{
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
}

void	ignore_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

static void	reset_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
}
