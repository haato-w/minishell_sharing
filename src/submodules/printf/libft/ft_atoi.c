/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesasaki <mesasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:01:19 by haatwata          #+#    #+#             */
/*   Updated: 2025/08/13 20:22:01 by mesasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*remove_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
	{
		i++;
	}
	return ((char *)(&str[i]));
}

static char	*remove_sign(const char *str)
{
	if (*str == '+' || *str == '-')
		return ((char *)(str + 1));
	return ((char *)(str));
}

static bool	is_valid_sign(const char *str)
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

long long	str2long(char *str, bool positive)
{
	long long	ret;
	int			digit_count;
	char		*p;

	digit_count = 0;
	p = str;
	while ('0' <= *p && *p <= '9')
	{
		digit_count++;
		p++;
	}
	if (digit_count > 19)
	{
		if (positive)
			return (LLONG_MAX);
		else
			return (LLONG_MIN);
	}
	ret = 0;
	while ('0' <= *str && *str <= '9')
	{
		if ((positive && ret > (LLONG_MAX - (*str - '0')) / 10)
			|| (!positive && ret > (-(LLONG_MIN + (*str - '0'))) / 10))
		{
			if (positive)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		ret = ret * 10 + (*str - '0');
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
