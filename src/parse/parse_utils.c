/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:07:03 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 13:16:56 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}

void	append_tok(t_token **tok, t_token *elm)
{
	if (*tok == NULL)
	{
		*tok = elm;
		return ;
	}
	append_tok(&(*tok)->next, elm);
}
