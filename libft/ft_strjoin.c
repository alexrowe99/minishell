/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:58:45 by nspeedy           #+#    #+#             */
/*   Updated: 2021/09/28 17:17:24 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	slen1;
	size_t	slen2;
	char	*dest;

	slen1 = 0;
	slen2 = 0;
	if (!s1 || !s2)
		return (0);
	dest = (char *)malloc(sizeof(char) * (sizeof(s1) + sizeof(s2) - 1));
	while (s1[slen1])
	{
		dest[slen1] = s1[slen1];
		slen1++;
	}
	while (s2[slen2])
	{
		dest[slen1 + slen2] = s2[slen2];
		slen2++;
	}
	dest[slen1 + slen2] = '\0';
	return (dest);
}
