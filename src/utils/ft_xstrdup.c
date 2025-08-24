/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:46:42 by heart             #+#    #+#             */
/*   Updated: 2025/08/24 21:10:34 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_xstrdup(const char *s1, t_context g_ctx)
{
	char	*ret;

	ret = ft_strdup(s1);
	if (ret == NULL)
		fatal_error("xstrdup", g_ctx);
	return (ret);
}
