#include "rtv1.h"

unsigned int	ret_colors(t_color colo)
{
	unsigned int	total;
	unsigned int	temp;

	total = 0;
	if (colo.r > 0)
	{
		temp = (int)colo.r * 256 * 256;
		total += temp;
	}
	if (colo.g > 0)
	{
		temp = (int)colo.g * 256;
		total += temp;
	}
	if (colo.b > 0)
	{
		temp = (int)colo.b;
		total += temp;
	}
	return (total);
}

t_color			c_color(float r, float g, float b)
{
	t_color		color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}