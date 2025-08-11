/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:56:14 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/11 19:37:53 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define ERROR_PREFIX "minishell: "

void	perror_prefix(void)
{
	ft_dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	xperror2(const char *s1, const char *err_msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s1);
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		perror(NULL);
}

void	xperror3(const char *s1, const char *s2, const char *err_msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s1);
	ft_dprintf(STDERR_FILENO, "%s: ", s2);
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		perror(NULL);
}

void	xperror_invalid_identifier(const char *s, const char *identifier)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s);
	ft_dprintf(STDERR_FILENO, "`%s': ", identifier);
	ft_dprintf(STDERR_FILENO, "not a valid identifier\n");
}
