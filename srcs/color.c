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

t_color			copy_color(t_color color)
{
	t_color		newcolor;

	newcolor.r = color.r;
	newcolor.g = color.g;
	newcolor.b = color.b;
	return (newcolor);
}

t_color			color_mult(t_color color, float taux, float limit)
{
	t_color		new_color;

	new_color = copy_color(color);
	new_color.r = (color.r == 0 && taux > limit) ? 128 * taux : color.r * taux;
	new_color.g = (color.g == 0 && taux > limit) ? 128 * taux : color.g * taux;
	new_color.b = (color.b == 0 && taux > limit) ? 128 * taux : color.b * taux;
	new_color.r = (new_color.r > 255) ? 255 : new_color.r;
	new_color.g = (new_color.g > 255) ? 255 : new_color.g;
	new_color.b = (new_color.b > 255) ? 255 : new_color.b;
	new_color.r = (new_color.r < 0) ? 0 : new_color.r;
	new_color.g = (new_color.g < 0) ? 0 : new_color.g;
	new_color.b = (new_color.b < 0) ? 0 : new_color.b;
	return (new_color);
}
