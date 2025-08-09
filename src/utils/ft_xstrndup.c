/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:46:42 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 16:28:18 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_xstrndup(const char *s1, size_t size)
{
	char	*ret;

	ret = ft_strndup(s1, size);
	if (ret == NULL)
		fatal_error("xstrndup");
	return (ret);
}
