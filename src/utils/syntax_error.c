/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:56:50 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/10 18:57:04 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize_error(const char *location, char **rest, char *line)
{
	g_ctx.syntax_error = true;
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "syntax errror near %s\n", location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *tok)
{
	g_ctx.syntax_error = true;
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "syntax error near unexpected token `%s' in %s\n",
		tok->word, location);
	while (tok && !at_eof(tok))
		tok = tok->next;
	*rest = tok;
}
