/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intensity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:23:02 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 20:25:20 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

float		obj_isnt_in_shadow(t_rt *e, t_vec3 poi, t_light *light)
{
	t_ray	ray;
	float	dist;
	float	dist_to_light;
	float	opac;
	int		i;
	t_vec3	poi2;

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
		{
			if (dist > 0 && dist < dist_to_light && e->scene.obj[i].neg != 1
				&& e->scene.obj[i].mat.damier == 0)
				opac = e->scene.obj[i].mat.refract +
					e->scene.obj[i].mat.reflex;
			if (e->scene.obj[i].mat.refract && e->scene.obj[i].mat.damier
				&& dist > 0 && dist < dist_to_light)
			{
				poi2 = vec_add3(light->ray.pos,
					vec_scale3(light->ray.dir, dist));
				if (damier(&poi2))
					return (0);
				opac = e->scene.obj[i].mat.refract_rate;
			}
		}
	}
	return (opac);
}

float		spec_intensity(t_rt *e, t_ray light, t_vec3 poi, t_ray ray)
{
	float	intensity;
	t_ray	refl;
	t_obj	obj;

	obj = e->scene.obj[e->scene.id];
	if (obj.mat.spec == 0)
		return (0);
	refl = get_reflected_ray(e, light, poi);
	intensity = vec_dot3(refl.dir, vec_inv3(ray.dir));
	if (intensity <= 0.5)
		intensity = pow(intensity, 8);
	else
		intensity = 0;
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
	norm = object_norm(e->scene.obj[e->scene.id], poi,
		vec_sub3(CCAM.pos, poi), ray);
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
	intensity = dot * obj.mat.diff;
	return ((intensity < 0) ? 0 : intensity);
}
