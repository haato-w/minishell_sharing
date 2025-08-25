/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:48:10 by heart             #+#    #+#             */
/*   Updated: 2025/08/26 01:03:39 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_status;

static void	interpret(char *line, int *stat_loc, t_context *g_ctx)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line, g_ctx);
	if (at_eof(tok))
		;
	else if (g_ctx->syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(tok, g_ctx);
		if (g_ctx->syntax_error)
			*stat_loc = ERROR_PARSE;
		else
		{
			expand(node, g_ctx);
			*stat_loc = exec(node, tok, g_ctx);
		}
		free_node(node, g_ctx);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;
	t_context	g_ctx = {};

	rl_outstream = stderr;
	initenv(&g_ctx);
	setup_sig_event_hook();
	g_ctx.last_status = 0;
	while (1)
	{
		setup_input_sig(&g_ctx);
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		setup_execution_sig(&g_ctx);
		interpret(line, &g_ctx.last_status, &g_ctx);
		free(line);
	}
	map_del(g_ctx.envmap);
	return (g_ctx.last_status);
}
