/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 03:10:21 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:23:30 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		nbr_word(char *str)
{
	int pos;
	int word;

	word = 0;
	pos = 0;
	while (str[pos] == ' ' || str[pos] == 9 || str[pos] == 13)
		pos++;
	while (str[pos])
	{
		while (str[pos] == ' ' || str[pos] == 9 || str[pos] == 13)
			pos++;
		while (str[pos] != ' ' && str[pos] != 9 && str[pos] != 13 && str[pos])
			pos++;
		word++;
	}
	pos--;
	if (str[pos] == ' ' || str[pos] == 9 || str[pos] == 13)
		word--;
	return (word);
}

static	int		size_word(char *str, int i)
{
	int base;

	base = i;
	while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' && str[i])
	{
		i++;
	}
	return (i - base);
}

char			**ft_split_whitespace(char *str)
{
	char	**tab;
	int		i;
	int		wrd;
	int		ltr;

	i = 0;
	wrd = 0;
	if (!(tab = (char **)malloc(sizeof(char*) * (nbr_word(str) + 1))))
		return (NULL);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
		{
			ltr = 0;
			if ((tab[wrd] = malloc(sizeof(char) * size_word(str, i) + 1)) == 0)
				return (NULL);
			while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
				tab[wrd][ltr++] = str[i++];
			tab[wrd++][ltr] = '\0';
		}
	}
	tab[wrd] = NULL;
	return (tab);
}
