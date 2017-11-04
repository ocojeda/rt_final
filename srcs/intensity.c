/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intensity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:23:02 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:39:24 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int				norme_shadow(t_reflect *ref, float *opac, t_rt *e)
{
	t_vec3		poi2;

	if (e->scene.obj[ref->a].mat.refract &&
		e->scene.obj[ref->a].mat.damier && ref->min_dist > 0
		&& ref->min_dist < ref->total_distance)
	{
		poi2 = vec_add3(ref->light->ray.pos, vec_scale3(ref->light->ray.dir,
				ref->min_dist));
		if (damier(&poi2))
			return (1);
		*opac = e->scene.obj[ref->a].mat.refract_rate;
	}
	return (0);
}

float			obj_isnt_in_shadow(t_rt *e, t_vec3 poi, t_light *light)
{
	float		opac;
	t_reflect	ref;

	ref.light = light;
	opac = set_isnt_in_shadow(ref.light, &ref, poi);
	while (++ref.a < e->scene.nbr_obj)
	{
		ref.min_dist = intersect_obj(ref.ray, &e->scene.obj[ref.a], e);
		if (ref.min_dist > 0 && ref.min_dist < ref.total_distance
				&& e->scene.obj[ref.a].neg != 1)
		{
			if (ref.min_dist > 0 && ref.min_dist < ref.total_distance &&
		e->scene.obj[ref.a].neg != 1 && e->scene.obj[ref.a].mat.damier == 0)
			{
				if (e->scene.obj[ref.a].mat.refract)
					opac = 1 - e->scene.obj[ref.a].mat.refract_rate;
				else
					opac = e->scene.obj[ref.a].mat.refract_rate
					+ e->scene.obj[ref.a].mat.reflex;
			}
			if (norme_shadow(&ref, &opac, e))
				return (0);
		}
	}
	return (opac);
}

float			spec_intensity(t_rt *e, t_ray light, t_vec3 poi, t_ray ray)
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

float			intensity_obj(t_rt *e, t_vec3 poi, t_ray ray, t_light light)
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

float			diff_intensity(t_obj obj, float dot)
{
	float	intensity;

	if (obj.mat.diff == 0)
		return (0);
	intensity = dot * obj.mat.diff;
	return ((intensity < 0) ? 0 : intensity);
}
