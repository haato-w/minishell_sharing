/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwata <haatwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:01:19 by haatwata          #+#    #+#             */
/*   Updated: 2024/03/22 00:35:32 by haatwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static	char	*remove_sign(const char *str)
{
	if (*str == '+' || *str == '-')
		return ((char *)(str + 1));
	return ((char *)(str));
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

static	long long	str2long(char *str, bool positive)
{
	long long	ret;

	ret = 0;
	while ('0' <= *str && *str <= '9')
	{
		if (positive)
		{
			if (ret / 10 < LLONG_MAX / 10 || \
				(ret / 10 == LLONG_MAX / 10 && ret % 10 <= LLONG_MAX % 10))
				ret = ret * 10 + (*str - '0');
			else
				return (LLONG_MAX);
		}
		else
		{
			if (ret / 10 < -(LLONG_MIN / 10) || \
				(ret / 10 == -(LLONG_MIN / 10) && ret % 10 < -(LLONG_MIN % 10)))
				ret = ret * 10 + (*str - '0');
			else
				return (LLONG_MIN);
		}
		str++;
	}
	return (ret);
}

int	ft_atoi(const char *str)
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
	preprocessed_str = remove_sign(removed_str);
	ret = str2long(preprocessed_str, positive);
	if (!positive)
		ret = (-1) * ret;
	return ((int)ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s1 = " ---+--+1234ab567";
// 	char *s2 = "111";
// 	char *s3 = "";
// 	char *s4 = " ---+--+";
// 	printf("%d\n", ft_atoi(s1));
// 	printf("%d\n", ft_atoi(s2));
// 	printf("%d\n", ft_atoi(s3));
// 	printf("%d\n", ft_atoi(s4));
// }
