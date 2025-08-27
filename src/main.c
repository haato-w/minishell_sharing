/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:48:10 by heart             #+#    #+#             */
/*   Updated: 2025/08/27 19:51:20 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_status;

int	*get_last_status(void)
{
	static int	last_status;

	return (&last_status);
}

bool	*get_readline_interrupted(void)
{
	static bool	readline_interrupted;

	return (&readline_interrupted);
}

static void	interpret(char *line, t_context *g_ctx)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line, g_ctx);
	if (at_eof(tok))
		;
	else if (g_ctx->syntax_error)
		*get_last_status() = ERROR_TOKENIZE;
	else
	{
		node = parse(tok, g_ctx);
		if (g_ctx->syntax_error)
			*get_last_status() = ERROR_PARSE;
		else
		{
			expand(node, g_ctx);
			*get_last_status() = exec(node, tok, g_ctx);
		}
		free_node(node, g_ctx);
	}
	free_tok(tok);
}

int	main(void)
{
	char		*line;
	t_context	g_ctx;

	rl_outstream = stderr;
	initenv(&g_ctx);
	setup_sig_event_hook();
	*get_last_status() = 0;
	while (1)
	{
		setup_input_sig(&g_ctx);
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		setup_execution_sig(&g_ctx);
		interpret(line, &g_ctx);
		free(line);
	}
	map_del(g_ctx.envmap);
	return (*get_last_status());
}
