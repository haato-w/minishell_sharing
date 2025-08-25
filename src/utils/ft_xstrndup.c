/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heart <heart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:46:42 by heart             #+#    #+#             */
/*   Updated: 2025/08/26 00:39:11 by heart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_xstrndup(const char *s1, size_t size, t_context *g_ctx)
{
	char	*ret;

	ret = ft_strndup(s1, size);
	if (ret == NULL)
		fatal_error("xstrndup", g_ctx);
	return (ret);
}
