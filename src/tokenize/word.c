/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:49:52 by heart             #+#    #+#             */
/*   Updated: 2025/08/26 00:46:54 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	consume_single_quote(char **rest, char *line, t_context *g_ctx)
{
	if (*line == SINGLE_QUOTE_CHAR)
	{
		line++;
		while (*line && *line != SINGLE_QUOTE_CHAR)
			line++;
		if (*line == '\0')
			tokenize_error("Unclosed single quote", &line, line, g_ctx);
		else
			line++;
		*rest = line;
		return (true);
	}
	return (false);
}

static bool	consume_double_quote(char **rest, char *line, t_context *g_ctx)
{
	if (*line == DOUBLE_QUOTE_CHAR)
	{
		line++;
		while (*line && *line != DOUBLE_QUOTE_CHAR)
			line++;
		if (*line == '\0')
			tokenize_error("Unclosed double quote", &line, line, g_ctx);
		else
			line++;
		*rest = line;
		return (true);
	}
	return (false);
}

t_token	*word(char **rest, char *line, t_context *g_ctx)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
	{
		if (consume_single_quote(&line, line, g_ctx))
			;
		else if (consume_double_quote(&line, line, g_ctx))
			;
		else
			line++;
	}
	word = ft_xstrndup(start, line - start, g_ctx);
	*rest = line;
	return (new_token(word, TK_WORD, g_ctx));
}
