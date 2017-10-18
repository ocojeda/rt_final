/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 22:44:50 by mhalit            #+#    #+#             */
/*   Updated: 2016/11/13 22:56:52 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	while (*s)
		s++;
	if (c == '\0')
		return ((char*)s);
	s--;
	while (*s)
	{
		if (*s == c)
			return ((char*)s);
		s--;
	}
	return (NULL);
}