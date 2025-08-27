/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:22:13 by heart             #+#    #+#             */
/*   Updated: 2025/08/27 18:43:33 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_single_quote(char **dst, char **rest, char *p, t_context *g_ctx)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		p++;
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed single quote", g_ctx);
			append_char(dst, *p++, g_ctx);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected single quote", g_ctx);
}

static void	remove_double_quote(char **dst, char **rest, char *p, t_context *g_ctx)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		p++;
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed double quote", g_ctx);
			append_char(dst, *p++, g_ctx);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected double quote", g_ctx);
}

static void	remove_quote(t_token *tok, t_context *g_ctx)
{
	char	*new_word;
	char	*p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc", g_ctx);
	while (*p)
	{
		if (*p == SINGLE_QUOTE_CHAR)
			remove_single_quote(&new_word, &p, p, g_ctx);
		else if (*p == DOUBLE_QUOTE_CHAR)
			remove_double_quote(&new_word, &p, p, g_ctx);
		else
			append_char(&new_word, *p++, g_ctx);
	}
	free(tok->word);
	tok->word = new_word;
	remove_quote(tok->next, g_ctx);
}

void	expand_quote_removal(t_node *node, t_context *g_ctx)
{
	if (node == NULL)
		return ;
	remove_quote(node->args, g_ctx);
	remove_quote(node->filename, g_ctx);
	remove_quote(node->delimiter, g_ctx);
	expand_quote_removal(node->redirects, g_ctx);
	expand_quote_removal(node->command, g_ctx);
	expand_quote_removal(node->next, g_ctx);
}
