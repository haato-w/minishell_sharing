/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:49:52 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 12:56:38 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	consume_single_quote(char **rest, char *line)
{
	if (*line == SINGLE_QUOTE_CHAR)
	{
		line++;
		while (*line && *line != SINGLE_QUOTE_CHAR)
			line++;
		if (*line == '\0')
			tokenize_error("Unclosed single quote", &line, line);
		else
			line++;
		*rest = line;
		return (true);
	}
	return (false);
}

static bool	consume_double_quote(char **rest, char *line)
{
	if (*line == DOUBLE_QUOTE_CHAR)
	{
		line++;
		while (*line && *line != DOUBLE_QUOTE_CHAR)
			line++;
		if (*line == '\0')
			tokenize_error("Unclosed double quote", &line, line);
		else
			line++;
		*rest = line;
		return (true);
	}
	return (false);
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
	{
		if (consume_single_quote(&line, line))
			;
		else if (consume_double_quote(&line, line))
			;
		else
			line++;
	}
	word = ft_xstrndup(start, line - start);
	*rest = line;
	return (new_token(word, TK_WORD));
}
