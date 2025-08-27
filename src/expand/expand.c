/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:35:01 by heart             #+#    #+#             */
/*   Updated: 2025/08/27 19:42:54 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_char(char **s, char c, t_context *g_ctx)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc", g_ctx);
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

static void	append_num(char **dst, unsigned int num, t_context *g_ctx)
{
	if (num == 0)
	{
		append_char(dst, '0', g_ctx);
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10, g_ctx);
	append_char(dst, '0' + (num % 10), g_ctx);
}

void	expand_special_parameter_str(char **dst, char **rest, char *p, t_context *g_ctx)
{
	if (!is_special_paramer(p))
		assert_error("Expected special parameter", g_ctx);
	p += 2;
	append_num(dst, *get_last_status(), g_ctx);
	*rest = p;
}

void	expand(t_node *node, t_context *g_ctx)
{
	expand_variable(node, g_ctx);
	expand_quote_removal(node, g_ctx);
}

char	*expand_heredoc_line(char *line, t_context *g_ctx)
{
	char	*new_word;
	char	*p;

	p = line;
	new_word = ft_xcalloc(1, sizeof(char), g_ctx);
	while (*p)
	{
		if (is_variable(p))
			expand_variable_str(&new_word, &p, p, g_ctx);
		else if (is_special_paramer(p))
			expand_special_parameter_str(&new_word, &p, p, g_ctx);
		else
			append_char(&new_word, *p++, g_ctx);
	}
	free(line);
	return (new_word);
}
