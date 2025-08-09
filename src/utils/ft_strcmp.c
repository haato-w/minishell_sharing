/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:11:58 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/09 22:26:31 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	min(size_t v1, size_t v2)
{
	if (v1 < v2)
		return (v1);
	else
		return (v2);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	len;

	len = min(ft_strlen(s1), ft_strlen(s2)) + 1;
	return (ft_strncmp(s1, s2, len));
}
