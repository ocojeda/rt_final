#include "../includes/rt.h"

t_color			get_text_color(int x, int y, t_texture tex)
{
	int			c;
	t_color		color;
	int			pos;

	if (x < tex.width && y < tex.height && x >= 0 && y >= 0)
	{
		pos = (x * tex.bpp / 8) + (y * tex.sizl);
		c = *(int*)&(tex.data[pos]);
		color.r = c / 65536 % 256;
		color.g = c / 256 % 256;
		color.b = c % 256;
		return (color);
	}
	return ((t_color){0, 0, 0, 0});
}

t_color			skybox(t_rt *e, t_ray ray)
{
	t_color		color_sky;
	t_vec2		uv;
	t_vec3		norm;
	int			i;
	float		intensity;

	i = -1;
	intensity = 0;
	color_sky = (t_color){0, 0, 0, 0};
	//while (++i < e->scene.nbr_light)
	//	intensity += dazzling_light(e, e->CLIGHT, vec_norme3(ray.dir));
	//while (++i < e->scene.nbr_light)
	//	intensity = 1;
	if (!(e->scene.skybox.is_init))
		return (color_mult((t_color){0, 0, 0, 0}, intensity, 0));
	norm = vec_norme3(ray.dir);
	uv.x = atan2(norm.x, norm.z) / (2 * M_PI) + 0.5;
	uv.y = norm.y * 0.5 + 0.5;
	uv.x = e->scene.skybox.width * (1 - uv.x);
	uv.y = e->scene.skybox.height * (1 - uv.y);
	return(color_sky = get_text_color((int)uv.x, (int)uv.y, e->scene.skybox));
	//intensity *= (color_is_black(&color_sky)) ? 100 : 5;
	return (color_mult(color_sky, 1 + intensity, 0));
}
