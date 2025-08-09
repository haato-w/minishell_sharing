/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:46:42 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 16:29:05 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_xstrdup(const char *s1)
{
	char	*ret;

	ret = ft_strdup(s1);
	if (ret == NULL)
		fatal_error("xstrdup");
	return (ret);
}
