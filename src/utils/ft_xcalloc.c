/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:39:22 by heart             #+#    #+#             */
/*   Updated: 2025/08/24 21:09:12 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_xcalloc(size_t count, size_t size, t_context g_ctx)
{
	void	*ret;

	ret = ft_calloc(count, size);
	if (ret == NULL)
		fatal_error("xcalloc", g_ctx);
	return (ret);
}
