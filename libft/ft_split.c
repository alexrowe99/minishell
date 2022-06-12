/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:21:06 by nspeedy           #+#    #+#             */
/*   Updated: 2021/09/25 14:15:01 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static int	ft_wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s == c)
		s++;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

static int	ft_find_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
		words++;
	}
	return (words);
}

static char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*result;

	result = (char *)malloc(sizeof(char) * (n + 1));
	if (!result)
		return (0);
	i = 0;
	while (i < n)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

static char	**ft_freee(char **s, int i)
{
	while (i--)
		free(s[i]);
	free(s);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;
	int		wordlen;
	int		i;

	if (!s)
		return (0);
	count = ft_find_words(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	i = 0;
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		wordlen = ft_wordlen(s, c);
		result[i] = ft_strndup(s, wordlen);
		if (!result)
			return (ft_freee(result, i));
		s += wordlen;
		i++;
	}
	result[count] = 0;
	return (result);
}
