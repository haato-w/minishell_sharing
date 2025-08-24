/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haatwat <haatwata@student.42tokyo.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:31:50 by haatwat           #+#    #+#             */
/*   Updated: 2024/08/18 18:41:52 by haatwat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	free_all(char **arr, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		free(arr[i]);
	}
	free(arr);
}

static	size_t	cnt_words(char const *s, char c)
{
	size_t	i;
	size_t	s_len;
	size_t	cnt;

	s_len = ft_strlen(s);
	i = 0;
	cnt = 0;
	while (i < s_len)
	{
		if ((i == 0 && s[i] != c) \
			|| (0 < i && s[i - 1] == c && s[i] != c))
		{
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static	char	*split_word(char const *s, char c, size_t start_idx)
{
	size_t	i;
	size_t	s_len;
	size_t	word_len;
	char	*ret;

	s_len = ft_strlen(s);
	i = start_idx;
	while (i < s_len && s[i] != c)
	{
		i++;
	}
	word_len = i - start_idx;
	ret = (char *)ft_calloc(sizeof(char), word_len + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		ret[i] = s[start_idx + i];
		i++;
	}
	ret[word_len] = '\0';
	return (ret);
}

static	char	**split_words(char const *s, char c, char **arr, size_t s_len)
{
	size_t	i;
	size_t	cnt;
	char	*word;

	i = 0;
	cnt = 0;
	while (i < s_len)
	{
		if ((i == 0 && s[i] != c) \
			|| (0 < i && s[i - 1] == c && s[i] != c))
		{
			word = split_word(s, c, i);
			if (word == NULL)
			{
				free_all(arr, cnt);
				return (NULL);
			}
			arr[cnt] = word;
			cnt++;
		}
		i++;
	}
	arr[cnt] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_num;
	char	**ret;
	size_t	s_len;

	word_num = cnt_words(s, c);
	ret = (char **)ft_calloc(sizeof(char *), (word_num + 1));
	if (ret == NULL)
		return (NULL);
	if (word_num == 0)
	{
		ret[0] = NULL;
		return (ret);
	}
	s_len = ft_strlen(s);
	ret = split_words(s, c, ret, s_len);
	return (ret);
}

// #include <stdio.h>
// void show(char **arr)
// {
//   size_t i;

//   i = 0;
//   while (arr[i] != 0)
//   {
//     printf("%s\n", arr[i]);
//     i++;
//   }
// }

// int main(void)
// {
// 	char *s1 = "helloahello";
//   char c1 = 'a';
//   printf("s1--------\n");
//   show(ft_split(s1, c1));
// 	//printf("%s\n", ft_split(s1, c1));a
//   char *s2 = "aaaaaaaa";
//   char c2 = 'a';
//   printf("s2--------\n");
//   show(ft_split(s2, c2));
//   //printf("%s\n", ft_split(s2, c2));
//   char *s3 = "aaaahelloheaaaa";
//   char c3 = 'h';
//   printf("s3--------\n");
//   show(ft_split(s3, c3));
//   //printf("%s\n", ft_split(s3, c3));
//   char *s4 = "aaaaa";
//   char c4 = 0;
//   printf("s4--------\n");
//   show(ft_split(s4, c4));
//   //printf("%s\n", ft_split(s4, c4));
//   char *s5 = "";
//   char c5 = 0;
//   printf("s5--------\n");
//   show(ft_split(s5, c5));
//   //printf("%s\n", ft_split(s5, c5));

// 	char *s6 = "^^^1^^2a,^^^^3^^^^--h^^^^";
//   char c6 = '^';
//   printf("s6--------\n");
//   show(ft_split(s6, c6));
// }
