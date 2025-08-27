/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:01:19 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/27 21:40:38 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*remove_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t'
		|| str[i] == '\n'
		|| str[i] == '\v'
		|| str[i] == '\f'
		|| str[i] == '\r'
		|| str[i] == ' ')
	{
		i++;
	}
	return ((char *)(&str[i]));
}

static	bool	is_valid_sign(const char *str)
{
	if (str[0] == '+' || str[0] == '-')
	{
		if ('0' <= str[1] && str[1] <= '9')
		{
			return (true);
		}
		else
		{
			return (false);
		}
	}
	return (true);
}

static bool	update_value(long long *ret, char *str, bool positive)
{
	if (positive)
	{
		if (*ret > (LLONG_MAX - (*str - '0')) / 10)
		{
			errno = ERANGE;
			*ret = LLONG_MAX;
			return (false);
		}
		*ret = *ret * 10 + (*str - '0');
	}
	else
	{
		if (*ret < (LLONG_MIN + (*str - '0')) / 10)
		{
			errno = ERANGE;
			*ret = LLONG_MIN;
			return (false);
		}
		*ret = *ret * 10 - (*str - '0');
	}
	return (true);
}

static long long	str2longlong(char *str, bool positive)
{
	long long	ret;

	ret = 0;
	while ('0' <= *str && *str <= '9')
	{
		if (update_value(&ret, str, positive) == false)
			return (ret);
		str++;
	}
	return (ret);
}

long long	ft_atoll(const char *str)
{
	char		*removed_str;
	bool		positive;
	char		*preprocessed_str;
	long long	ret;

	removed_str = remove_space(str);
	if (!is_valid_sign(removed_str))
		return (0);
	positive = true;
	if (removed_str[0] == '-')
		positive = false;
	if (*removed_str == '+' || *removed_str == '-')
		preprocessed_str = removed_str + 1;
	else
		preprocessed_str = removed_str;
	ret = str2longlong(preprocessed_str, positive);
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s1 = " ---+--+1234ab567";
// 	char *s2 = "111";
// 	char *s3 = "";
// 	char *s4 = " ---+--+";
// 	printf("%lld\n", ft_atoll(s1));
// 	printf("%lld\n", ft_atoll(s2));
// 	printf("%lld\n", ft_atoll(s3));
// 	printf("%lld\n", ft_atoll(s4));
// }
