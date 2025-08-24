/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:33:20 by heart             #+#    #+#             */
/*   Updated: 2025/08/24 21:27:05 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	argv_len(t_token *tok)
{
	size_t	len;

	len = 0;
	while (tok && !at_eof(tok))
	{
		len++;
		tok = tok->next;
	}
	return (len);
}

char	**token_list_to_argv(t_token *tok, t_context g_ctx)
{
	char	**argv;
	size_t	i;

	argv = ft_xcalloc(argv_len(tok) + 1, sizeof(char *), g_ctx);
	i = 0;
	while (tok && !at_eof(tok))
	{
		argv[i] = ft_xstrdup(tok->word, g_ctx);
		i++;
		tok = tok->next;
	}
	return (argv);
}
