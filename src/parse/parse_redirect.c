/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:02:28 by heart             #+#    #+#             */
/*   Updated: 2025/08/26 00:45:37 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*redirect_out(t_token **rest, t_token *tok, t_context *g_ctx)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT, g_ctx);
	node->filename = tokdup(tok->next, g_ctx);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_in(t_token **rest, t_token *tok, t_context *g_ctx)
{
	t_node	*node;

	node = new_node(ND_REDIR_IN, g_ctx);
	node->filename = tokdup(tok->next, g_ctx);
	node->targetfd = STDIN_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_append(t_token **rest, t_token *tok, t_context *g_ctx)
{
	t_node	*node;

	node = new_node(ND_REDIR_APPEND, g_ctx);
	node->filename = tokdup(tok->next, g_ctx);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_heredoc(t_token **rest, t_token *tok, t_context *g_ctx)
{
	t_node	*node;

	node = new_node(ND_REDIR_HEREDOC, g_ctx);
	node->delimiter = tokdup(tok->next, g_ctx);
	if (ft_strchr(node->delimiter->word, SINGLE_QUOTE_CHAR) == NULL
		&& ft_strchr(node->delimiter->word, DOUBLE_QUOTE_CHAR) == NULL)
		node->is_delim_unquoted = true;
	node->targetfd = STDIN_FILENO;
	*rest = tok->next->next;
	return (node);
}
