/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:46:58 by heart             #+#    #+#             */
/*   Updated: 2025/08/26 00:42:21 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(char *word, t_token_kind kind, t_context *g_ctx)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc", g_ctx);
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

t_token	*operator(char **rest, char *line, t_context *g_ctx)
{
	static char *const	operators[] = {">>", "<<", "||", "&&",
		";;", "<", ">", "&", ";", "(", ")", "|", "\n"};
	size_t				i;
	char				*op;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = ft_strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup", g_ctx);
			*rest = line + ft_strlen(op);
			return (new_token(op, TK_OP, g_ctx));
		}
		i++;
	}
	assert_error("Unexpected operator", g_ctx);
}

t_token	*tokenize(char *line, t_context *g_ctx)
{
	t_token	head;
	t_token	*tok;

	g_ctx->syntax_error = false;
	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_metacharacter(*line))
		{
			tok->next = operator(&line, line, g_ctx);
			tok = tok->next;
		}
		else if (is_word(line))
		{
			tok->next = word(&line, line, g_ctx);
			tok = tok->next;
		}
		else
			tokenize_error("Unexpected Token", &line, line, g_ctx);
	}
	tok->next = new_token(NULL, TK_EOF, g_ctx);
	return (head.next);
}
