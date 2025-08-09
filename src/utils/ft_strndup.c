/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:46:42 by heart             #+#    #+#             */
/*   Updated: 2025/08/09 20:51:37 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*new;

	len = ft_strlen(s1);
	if (n < len)
		len = n;
	new = ft_calloc(len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_memmove(new, s1, len);
	return (new);
}
