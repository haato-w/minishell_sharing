/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:42:59 by heart             #+#    #+#             */
/*   Updated: 2025/08/13 02:33:28 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_state_heredoc(void)
{
	if (g_ctx.sig == 0)
		return (0);
	else if (g_ctx.sig == SIGINT)
	{
		g_ctx.sig = 0;
		rl_done = 1;
		g_ctx.last_status = 130;
		return (0);
	}
	return (0);
}

static int	check_state(void)
{
	if (g_ctx.sig == 0)
		return (0);
	else if (g_ctx.sig == SIGINT)
	{
		g_ctx.sig = 0;
		g_ctx.last_status = 130;
		return (0);
	}
	return (0);
}

void	setup_sig_event_hook_heredoc(void)
{
	// extern int	_rl_echo_control_chars;

	// _rl_echo_control_chars = 0;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state_heredoc;
}

void	setup_sig_event_hook(void)
{
	// extern int	_rl_echo_control_chars;

	// _rl_echo_control_chars = 0;
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
