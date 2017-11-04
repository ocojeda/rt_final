#include "../includes/rt.h"

t_color matiere_converter(t_ray *ray, t_obj *obj, t_reflect *ref, t_rt *e)
{
	float	dot;
	t_ray	ray_tmp;
	
	ray_tmp = get_reflected_ray(e, *ray, ref->poi);
	dot = sin(vec_dot3(ray->dir, ref->poi)) * PI;
	if(obj->mat.sinus == 1)
		return (bruit(dot, ref->color, e->scene.obj[e->scene.id].color, rand_noise((e->scene.x + e->scene.y) * e->scene.id)));
	if(obj->mat.sinus == 2)
		return (ft_map_color(bruit3(dot*0.9, e->scene.x, e->scene.y, e), c_color(163,60,80), 0.5));
	dot = vec_dot3(ray->dir, ray_tmp.pos) * obj->mat.sinus;
	return (bruit2(dot * obj->mat.sinus, c_color(150, 50, 200), e->scene.obj[e->scene.id].color, rand_noise(e->scene.x)));
}

t_color			get_color(t_rt *e, t_obj obj, t_vec3 poi, t_ray ray)
{
	float		intensity;
	int			i;
	t_color		color1;
	t_reflect	ref;

	ref.poi = poi;

	i = -1;
	intensity = (!e->scene.nbr_light) ? AMBIENT_LIGHT : 0;
	while (++i < e->scene.nbr_light)
		intensity += intensity_obj(e, poi, ray, e->CLIGHT);
	
	if (intensity != 0)
	{
		float	dot = vec_dot3(ray.dir, poi);
		color1 = color_mult(obj.color, intensity, 1);
		ref.color = color1;
		if(obj.mat.sinus)
			return (color_mult(matiere_converter(&ray, &obj, &ref, e), intensity, 1));
		return	ref.color;
	}
	return ((t_color){0, 0, 0, 0});
}