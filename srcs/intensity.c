#include "../includes/rt.h"

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
		dist = intersect_obj(ray, &e->scene.obj[i], e);
		if (dist > 0 && dist < dist_to_light && e->scene.obj[i].neg != 1)
			opac = e->scene.obj[i].mat.refract;
	}
	return (opac);
}

// float		intensity_obj(t_rt *e, t_vec3 poi, t_obj obj, t_light light)
// {
	// float	intensity;
	// t_vec3	norm;
	// float	transp;
	// float	dot;
	// t_vec3	refl;
// 
	// 
	// intensity = 0;
	// transp = 0;
	// light.ray.dir = vec_norme3(vec_sub3(light.ray.pos, poi));
	// norm = color_norm(obj, poi, e->scene.cam.pos);
	// if ((dot = vec_dot3(light.ray.dir, norm)) > 0
	// && (transp = obj_isnt_in_shadow(e, poi, &light)))
	// {
		// refl = vec_scale3(norm, 2 * dot);
		// refl = vec_sub3(light.ray.dir, refl);
		// intensity = vec_dot3(vec_scale3(light.ray.dir, -1), refl);
		// if(intensity < 0)
			// intensity = 0;
		// intensity = pow(intensity, (light.intensity)) * obj.mat.diff ;
	// }
	// return (intensity * transp + AMBIENT_LIGHT);
// 
// }

float		dazzling_light(t_rt *e, t_light light, t_vec3 cam_dir)
{
	float	intensity;
	float	dot;
	t_vec3	refl;
	float	transp;

	light.ray.dir = vec_sub3(light.ray.pos, CCAM.pos);
	if (!(transp = obj_isnt_in_shadow(e, CCAM.pos, &light)))
		return (0);
	light.ray.dir = vec_norme3(light.ray.dir);
	if ((dot = vec_dot3(light.ray.dir, cam_dir)) < EPSILON)
		return (0);
	refl = vec_sub3(light.ray.dir, vec_scale3(cam_dir, 2 * dot));
	intensity = vec_dot3(vec_scale3(light.ray.dir, -1), refl);
	return ((intensity < 0) ? 0 : pow(intensity, 500) * 2 * transp);
}

float		spec_intensity(t_rt *e, t_ray light, t_vec3 poi, t_ray ray)
{
	float	intensity;
	t_ray	refl;
	t_obj 	obj;
	
	obj = e->scene.obj[e->scene.id];
	if (obj.mat.spec == 0)
		return (0);
	refl = get_reflected_ray(e, light, poi);
	intensity = vec_dot3(refl.dir, vec_inv3(ray.dir));
	intensity = pow(intensity, 8);
	return (intensity);
}

float		intensity_obj(t_rt *e, t_vec3 poi, t_ray ray, t_light light)
{
	float	intensity;
	t_vec3	norm;
	float	transp;
	float	dot;

	intensity = 0;
	transp = 0;
	light.ray.dir = vec_norme3(vec_sub3(light.ray.pos, poi));
	norm = color_norm(e->scene.obj[e->scene.id], poi, vec_sub3(CCAM.pos, poi));
	if ((dot = vec_dot3(light.ray.dir, norm)) > 0
		&& (transp = obj_isnt_in_shadow(e, poi, &light)))
	{
		intensity += spec_intensity(e, light.ray, poi, ray);
		intensity += diff_intensity(e->scene.obj[e->scene.id], dot);
	}
	return (intensity * transp + AMBIENT_LIGHT);
}

float		diff_intensity(t_obj obj, float dot)
{
	float	intensity;

	if (obj.mat.diff == 0)
		return (0);
	intensity = dot* 1.5 * obj.mat.diff ;
	return ((intensity < 0) ? 0 : intensity);
}