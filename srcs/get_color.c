#include "../includes/rt.h"

t_color matiere_converter(t_ray *ray, t_obj *obj, t_reflect *ref, t_rt *e)
{
	float	dot;
	t_ray	ray_tmp;
	
	ray_tmp = get_reflected_ray(e, *ray, ref->poi);
	dot = sin(vec_dot3(ray->dir, ref->poi)) * PI;
	if(obj->mat.sinus == 1)
	{
		dot = vec_dot3(ray->dir, ref->poi);
		return(bruit2(dot * 1200, c_color(150,150,150), ref->color, 150));
	}
	if(obj->mat.sinus == 2)
		return (ft_map_color(bruit3(dot*0.9, e->scene.x, e->scene.y, e), c_color(163,60,80), 0.5));
	if(e->scene.obj[e->scene.id].mat.sinus == 3)
		return(bruit(sin(dot * e->scene.obj[e->scene.id].mat.sinus), ref->color, e->scene.obj[e->scene.id].color, (e->scene.x+ e->scene.y)));
	return(bruit((dot * e->scene.obj[e->scene.id].mat.sinus), ref->color, e->scene.obj[e->scene.id].color, (e->scene.x+ e->scene.y)));
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
		color1 = color_mult(obj.color, intensity, 1);
		ref.color = color1;
		ref.dist_rate = intensity;
		if(obj.mat.sinus)
			return (color_mult(matiere_converter(&ray, &obj, &ref, e), intensity, 1));
		return	ref.color;
	}
	return ((t_color){0, 0, 0, 0});
}