#include "rtv1.h"

float			obj_isnt_in_shadow(t_rt *e, t_vec3 poi, t_light *light)
{
	t_ray	ray;
	float	dist;
	float	dist_to_light;
	float	opac;
	int		i;

	i = -1;
	opac = 1;
	light->ray.dir = vec_sub3(light->ray.pos, poi);
	dist_to_light = get_length(light->ray.dir);
	light->ray.dir = vec_norme3(light->ray.dir);
	ray = c_ray(vec_add3(poi, light->ray.dir), light->ray.dir);
	while (++i < e->scene.nbr_obj)
	{
		dist = intersect_obj(ray, &e->scene.obj[i]);
		if (dist > 0 && dist < dist_to_light)
		{
			opac = 0;
		}
	}
	return (opac);
}

float		intensity_obj(t_rt *e, t_vec3 poi, t_obj obj, t_light light)
{
	float	intensity;
	t_vec3	norm;
	float	transp;
	float	dot;
	t_vec3	refl;

	intensity = 0;
	transp = 0;
	light.ray.dir = vec_norme3(vec_sub3(light.ray.pos, poi));
	norm = color_norm(obj, poi, vec_sub3(e->scene.cam.pos, poi));
	if ((dot = vec_dot3(light.ray.dir, norm)) > 0
	&& (transp = obj_isnt_in_shadow(e, poi, &light)))
	{
		refl = vec_scale3(norm, 2 * dot);
		refl = vec_sub3(light.ray.dir, refl);
		intensity = vec_dot3(vec_scale3(light.ray.dir, -1), refl);
		if(intensity < 0)
			intensity = 0;
		intensity = pow(intensity, 50);
		//dist_to_light = get_length(vec_sub3(light.ray.pos, poi));
		//dist_to_light = 1;
		//intensity += dot * 0.3 + (0.2 * dist_to_light / 100);
	}
	return (intensity * transp + AMBIENT_LIGHT);
}

float		diff_intensity(t_obj obj, float dot)
{
	float	intensity;

	if (obj.mat.diff == 0)
		return (0);
	intensity = dot	* obj.mat.diff;
	return ((intensity < 0) ? 0 : intensity);
}