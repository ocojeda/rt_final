#include "../includes/rt.h"

void		filter_black_and_white(t_rt *e)
{
	unsigned int	i;
	unsigned int	x;
	
	i = 0;
	while (i < (unsigned int)(LARGEUR * HAUTEUR * 4))
	{
		x = (unsigned char)DATA[i + 2] + (unsigned char)DATA[i + 1] + (unsigned char)DATA[i];
		x /= 3;
		*((unsigned int *)(DATA + i)) = x | x << 8 | x << 16 | (unsigned char)DATA[i + 3] << 24;
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
			(0.7 * (unsigned char)DATA[i + 1]) + (0.1 * (unsigned char)DATA[i]), 255.0);
	DATA[i + 1] = ft_min((0.2 * (unsigned char)DATA[i + 2]) +
			(0.6 * (unsigned char)DATA[i + 1]) + (0.1 * (unsigned char)DATA[i]), 255.0);
	DATA[i + 0] = ft_min((0.2 * (unsigned char)DATA[i + 2]) +
			(0.5 * (unsigned char)DATA[i + 1]) + (0.1 * (unsigned char)DATA[i]), 255.0);
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

void		filters(t_rt *e)
{
	if (e->scene.filters == 1)
		filter_black_and_white(e);
	if (e->scene.filters == 2)
		filter_sepia(e);
	if (e->scene.filters == 3)
		filter_reverse(e);
}