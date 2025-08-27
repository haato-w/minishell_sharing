/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:48:10 by heart             #+#    #+#             */
/*   Updated: 2025/08/27 20:18:52 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	sig;

t_context	*get_ctx(void)
{
	static t_context ctx;

	return (&ctx);
}

static void	interpret(char *line)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	if (at_eof(tok))
		;
	else if ((*get_ctx()).syntax_error)
		(*get_ctx()).last_status = ERROR_TOKENIZE;
	else
	{
		node = parse(tok);
		if ((*get_ctx()).syntax_error)
			(*get_ctx()).last_status = ERROR_PARSE;
		else
		{
			expand(node);
			(*get_ctx()).last_status = exec(node, tok);
		}
		free_node(node);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	sig = 0;
	initenv();
	setup_sig_event_hook();
	(*get_ctx()).last_status = 0;
	while (1)
	{
		setup_input_sig();
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		setup_execution_sig();
		interpret(line);
		free(line);
	}
	map_del((*get_ctx()).envmap);
	return ((*get_ctx()).last_status);
}
