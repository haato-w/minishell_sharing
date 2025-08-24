/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:46:42 by heart             #+#    #+#             */
/*   Updated: 2025/08/24 21:11:04 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_xstrndup(const char *s1, size_t size, t_context g_ctx)
{
	char	*ret;

	ret = ft_strndup(s1, size);
	if (ret == NULL)
		fatal_error("xstrndup", g_ctx);
	return (ret);
}
