/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:56:14 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/10 04:38:15 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define ERROR_PREFIX "minishell: "

void	perror_prefix(void)
{
	ft_dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

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

void	xperror(const char *locaton)
{
	perror_prefix();
	perror(locaton);
}

void	builtin_error(const char *func, const char *name, const char *err)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", func);
	if (name)
		ft_dprintf(STDERR_FILENO, "`%s': ", name);
	ft_dprintf(STDERR_FILENO, "%s\n", err);
}
