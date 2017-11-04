/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:46:33 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:23:58 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	int		j;
	int		i;
	char	swap;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	i--;
	j = 0;
	while (i > j)
	{
		swap = str[j];
		str[j] = str[i];
		str[i] = swap;
		i--;
		j++;
	}
	return (str);
}
