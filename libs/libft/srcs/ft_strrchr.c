/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 22:44:50 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:23:57 by bbeldame         ###   ########.fr       */
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
