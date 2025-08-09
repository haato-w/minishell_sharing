/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:46:58 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 12:59:11 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

t_token	*operator(char **rest, char *line)
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
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
}

t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*tok;

	g_ctx.syntax_error = false;
	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_metacharacter(*line))
		{
			tok->next = operator(&line, line);
			tok = tok->next;
		}
		else if (is_word(line))
		{
			tok->next = word(&line, line);
			tok = tok->next;
		}
		else
			tokenize_error("Unexpected Token", &line, line);
	}
	tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}
