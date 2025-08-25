/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:28:02 by heart             #+#    #+#             */
/*   Updated: 2025/08/26 00:48:16 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable_str(char **dst, char **rest, char *p, t_context *g_ctx)
{
	char	*name;
	char	*value;

	name = ft_calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc", g_ctx);
	if (*p != '$')
		assert_error("Expected dollar sign", g_ctx);
	p++;
	if (!is_alpha_under(*p))
		assert_error("Variable must starts with alphabetic \
			character of underscore.", g_ctx);
	while (is_alpha_num_under(*p))
		append_char(&name, *p++, g_ctx);
	value = xgetenv(name, g_ctx);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++, g_ctx);
	*rest = p;
}

static void	append_single_quote(char **dst, char **rest, char *p, t_context *g_ctx)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		append_char(dst, *p++, g_ctx);
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed single quote", g_ctx);
			append_char(dst, *p++, g_ctx);
		}
		append_char(dst, *p++, g_ctx);
		*rest = p;
	}
	else
		assert_error("Expected single quote", g_ctx);
}

static void	append_double_quote(char **dst, char **rest, char *p, t_context *g_ctx)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		append_char(dst, *p++, g_ctx);
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed double quote", g_ctx);
			else if (is_variable(p))
				expand_variable_str(dst, &p, p, g_ctx);
			else if (is_special_paramer(p))
				expand_special_parameter_str(dst, &p, p, g_ctx);
			else
				append_char(dst, *p++, g_ctx);
		}
		append_char(dst, *p++, g_ctx);
		*rest = p;
	}
	else
		assert_error("Expected double quote", g_ctx);
}

static void	expand_variable_tok(t_token *tok, t_context *g_ctx)
{
	char	*new_word;
	char	*p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc", g_ctx);
	while (*p && !is_metacharacter(*p))
	{
		if (*p == SINGLE_QUOTE_CHAR)
			append_single_quote(&new_word, &p, p, g_ctx);
		else if (*p == DOUBLE_QUOTE_CHAR)
			append_double_quote(&new_word, &p, p, g_ctx);
		else if (is_variable(p))
			expand_variable_str(&new_word, &p, p, g_ctx);
		else if (is_special_paramer(p))
			expand_special_parameter_str(&new_word, &p, p, g_ctx);
		else
			append_char(&new_word, *p++, g_ctx);
	}
	free(tok->word);
	tok->word = new_word;
	expand_variable_tok(tok->next, g_ctx);
}

void	expand_variable(t_node *node, t_context *g_ctx)
{
	if (node == NULL)
		return ;
	expand_variable_tok(node->args, g_ctx);
	expand_variable_tok(node->filename, g_ctx);
	expand_variable(node->redirects, g_ctx);
	expand_variable(node->command, g_ctx);
	expand_variable(node->next, g_ctx);
}
