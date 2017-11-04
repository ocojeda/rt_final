#include "../includes/rt.h"

float rand_noise(int t)
{
    t = (t<<13) ^ t;
    t = (t * (t * t * 15731 + 789221) + 1376312589);
    return 1.0 - (t & 0x7fffffff) / 1073741824.0;
}

t_color			get_color(t_rt *e, t_obj obj, t_vec3 poi, t_ray ray)
{
	float		intensity;
	int			i;
	t_color		color1;
	t_ray		ray_tmp;

	i = -1;
	intensity = (!e->scene.nbr_light) ? AMBIENT_LIGHT : 0;
	while (++i < e->scene.nbr_light)
		intensity += intensity_obj(e, poi, ray, e->CLIGHT);
	
	if (intensity != 0)
	{
		float	dot = vec_dot3(ray.dir, poi);
		
		ray_tmp = get_reflected_ray(e, ray, poi);
		dot = vec_dot3(ray.dir, poi);
	
		color1 = color_mult(obj.color, intensity, 1);
		dot = sin(vec_dot3(ray.dir, poi))*PI;
		if(obj.mat.sinus == 1)
			return (color_mult(bruit(dot, color1, e->scene.obj[e->scene.id].color, rand_noise(e->scene.x)), intensity, 1)); 
		if(obj.mat.sinus == 2)
			return (ft_map_color(color_mult(bruit3(dot*0.9, e->scene.x, e->scene.y, e), intensity, 1), c_color(163,60,80), 0.5));
		if(obj.mat.sinus >= 3)
		{
			dot = vec_dot3(ray.dir, ray_tmp.pos) * obj.mat.sinus;
			return (color_mult(bruit2(dot * obj.mat.sinus, c_color(150, 50, 200), e->scene.obj[e->scene.id].color, rand_noise(e->scene.x)), intensity, 1));
		}
		return	color1;
	}
	return ((t_color){0, 0, 0, 0});
}
int		begin_raytracer(t_rt *e, t_ray *ray, t_reflect *ref)
{
	float		tmp;

	if ((ref->min_dist = get_min_dist(e, *ray)) == -1)
	{
		ref->color = c_color(0,0,0);
		return (1);
	}
	ref->type = e->scene.obj[e->scene.id].type;
	ref->tmp_id = e->scene.id;
	ref->poi = vec_add3(ray->pos, vec_scale3(ray->dir, ref->min_dist));
	ref->counter = NR_ITER;
	ref->ray = c_ray(ray->pos, ray->dir);
	ref->total_distance = ref->min_dist;
	if (e->scene.obj[e->scene.id].mat.reflex == 1)
	{
		tmp = e->scene.obj[e->scene.id].mat.reflex_filter;
		ref->color = get_color(e, e->scene.obj[e->scene.id], ref->poi, *ray);
		e->scene.id = ref->tmp_id;
		ref->color = ft_map_color(get_refracted_color(e, ref->poi, ref->color, *ref), ref->color, tmp);
		return (1);
	}
	return (0);
}

t_color		refract_or_damier(t_rt *e, t_ray *ray, t_reflect *ref)
{
	t_ray 	ray2;
	float 	min_dist2;
	float	tmp;
	t_vec3	poi2;

	if (e->scene.obj[e->scene.id].mat.damier == 1)
	{
		if(damier(&ref->poi, e))
			return (get_color(e, e->scene.obj[e->scene.id], ref->poi, *ray));
		if (e->scene.obj[e->scene.id].type != PLANE)
		{
			ray2.pos = vec_add3(ref->poi, ray->dir);
			ray2.dir = vec_cpy3(ray->dir);
			min_dist2 = intersect_obj(ray2, &e->scene.obj[e->scene.id], e);
			if(min_dist2)
			{
				poi2 = vec_add3(ray2.pos, vec_scale3(ray2.dir, min_dist2));
				if(damier(&poi2, e))
					return (get_color(e, e->scene.obj[e->scene.id], poi2, ray2));
			}
			min_dist2 = 0;
		}
	}
	tmp = e->scene.obj[e->scene.id].mat.refract_filter;
	ref->color = get_color(e, e->scene.obj[e->scene.id], ref->poi, *ray);
	e->scene.id = ref->tmp_id;
	ref->color = ft_map_color(get_refracted_color(e, ref->poi, ref->color, *ref), ref->color, tmp);
	return (ref->color);
}

t_color	get_pxl_color(t_rt *e, t_ray ray)
{
	t_reflect	ref;
	float		tmp;
	t_ray		ray2;
	t_vec3		poi2;
	float		min_dist2;

	if (begin_raytracer(e, &ray, &ref))
		return ref.color;
	else if (e->scene.obj[e->scene.id].mat.refract == 1)
		return (refract_or_damier(e, &ray, &ref));
	else
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi, ray);
	return (ref.color);
}

t_color			raytrace(int x, int y, t_rt *e)
{
	t_color		color;
	t_ray		ray;

	e->scene.x = x;
	e->scene.y = y;
	e->scene.id = -1;
	ray = ray_init(e, x * RES / ALIASING, y * RES / ALIASING);
	color = get_pxl_color(e, ray);
	return (color);
}
