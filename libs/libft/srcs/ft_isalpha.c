/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:41:50 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:23:04 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalpha(int c)
{
	int	mincl;
	int maxcl;
	int	min;
	int max;

	min = 'a';
	max = 'z';
	mincl = 'A';
	maxcl = 'Z';
	if ((c >= min && c <= max) || (c >= mincl && c <= maxcl))
		return (1);
	else
		return (0);
}
