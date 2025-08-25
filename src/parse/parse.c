/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:07:33 by heart             #+#    #+#             */
/*   Updated: 2025/08/26 00:43:47 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_control_operator(t_token *tok)
{
	static char *const	operators[] = {"||", "&", "&&", ";", ";;",
		"(", ")", "|", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(tok->word, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

void	append_command_element(t_node *command, t_token **rest, t_token *tok, t_context *g_ctx)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&command->args, tokdup(tok, g_ctx));
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_out(&tok, tok, g_ctx));
	else if (equal_op(tok, "<") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_in(&tok, tok, g_ctx));
	else if (equal_op(tok, ">>") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_append(&tok, tok, g_ctx));
	else if (equal_op(tok, "<<") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_heredoc(&tok, tok, g_ctx));
	else
		parse_error("append_command_element", &tok, tok, g_ctx);
	*rest = tok;
}

static t_node	*simple_command(t_token **rest, t_token *tok, t_context *g_ctx)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD, g_ctx);
	append_command_element(node, &tok, tok, g_ctx);
	while (tok && !at_eof(tok) && !is_control_operator(tok))
		append_command_element(node, &tok, tok, g_ctx);
	*rest = tok;
	return (node);
}

static t_node	*pipeline(t_token **rest, t_token *tok, t_context *g_ctx)
{
	t_node	*node;

	node = new_node(ND_PIPELINE, g_ctx);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&tok, tok, g_ctx);
	if (equal_op(tok, "|"))
		node->next = pipeline(&tok, tok->next, g_ctx);
	*rest = tok;
	return (node);
}

t_node	*parse(t_token *tok, t_context *g_ctx)
{
	return (pipeline(&tok, tok, g_ctx));
}
