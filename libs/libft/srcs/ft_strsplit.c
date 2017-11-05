/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 14:45:11 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:23:58 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordsnbr(const char *s, char c)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (*s != '\0')
	{
		if (j == 1 && *s == c)
			j = 0;
		if (j == 0 && *s != c)
		{
			j = 1;
			i++;
		}
		s++;
	}
	return (i);
}

static int	wordslen(const char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		words;
	int		i;

	if (!c || !s)
		return (NULL);
	i = 0;
	words = wordsnbr((const char*)s, c);
	str = (char **)malloc(sizeof(*str) * (wordsnbr((const char *)s, c) + 1));
	if (!str)
		return (NULL);
	while (words--)
	{
		while (*s == c && *s != '\0')
			s++;
		str[i] = ft_strsub((const char*)s, 0, wordslen((const char *)s, c));
		if (str[i] == NULL)
			return (NULL);
		s = s + wordslen((const char *)s, c);
		i++;
	}
	str[i] = NULL;
	return (str);
}
