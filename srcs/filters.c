/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:31:14 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/05 16:34:02 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		filter_black_and_white(t_rt *e)
{
	unsigned int	i;
	unsigned int	x;

	i = 0;
	while (i < (unsigned int)(LARGEUR * HAUTEUR * 4))
	{
		x = (unsigned char)DATA[i + 2] + (unsigned char)DATA[i + 1]
			+ (unsigned char)DATA[i];
		x /= 3;
		*((unsigned int *)(DATA + i)) = x | x << 8 |
			x << 16 | (unsigned char)DATA[i + 3] << 24;
		i += 4;
	}
}

void		filter_sepia(t_rt *e)
{
	unsigned int	i;

	i = 0;
	while (i < (unsigned int)(LARGEUR * HAUTEUR * 4))
	{
		DATA[i + 2] = ft_min((0.3 * (unsigned char)DATA[i + 2]) +
			(0.7 * (unsigned char)DATA[i + 1]) +
				(0.1 * (unsigned char)DATA[i]), 255.0);
		DATA[i + 1] = ft_min((0.2 * (unsigned char)DATA[i + 2]) +
			(0.6 * (unsigned char)DATA[i + 1]) +
				(0.1 * (unsigned char)DATA[i]), 255.0);
		DATA[i + 0] = ft_min((0.2 * (unsigned char)DATA[i + 2]) +
			(0.5 * (unsigned char)DATA[i + 1]) +
				(0.1 * (unsigned char)DATA[i]), 255.0);
		i += 4;
	}
}

void		filter_reverse(t_rt *e)
{
	unsigned int	i;

	i = 0;
	while (i < (unsigned int)(LARGEUR * HAUTEUR * 4))
	{
		DATA[i] = 255 - (unsigned char)DATA[i];
		DATA[i + 1] = 255 - (unsigned char)DATA[i + 1];
		DATA[i + 2] = 255 - (unsigned char)DATA[i + 2];
		i += 4;
	}
}

void		filter_stereo(t_rt *e)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < (LARGEUR * HAUTEUR * 4))
	{
		tmp = i + 1 - 40 - (LARGEUR * 4) * 10;
		if (tmp > 0)
		{
			DATA[tmp] = DATA[i + 1];
			DATA[i + 1] = 0;
			tmp = i - 40 - (LARGEUR * 4) * 10;
			DATA[tmp] = DATA[i];
			DATA[i] = 0;
		}
		i += 4;
	}
}

void		filters(t_rt *e)
{
	if (e->scene.filters == 1)
		filter_black_and_white(e);
	if (e->scene.filters == 2)
		filter_sepia(e);
	if (e->scene.filters == 3)
		filter_reverse(e);
	if (e->scene.filters == 4)
		filter_stereo(e);
}
