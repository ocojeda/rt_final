/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:10:12 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:41:20 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

float			find_min_dist_for_refref(t_rt *e, int *a, t_ray ray)
{
	float		min_dist;
	float		dist;
	int			i;

	i = 0;
	dist = 0;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		if (i != e->scene.id)
		{
			dist = get_min_dist(e, ray);
			if (dist < min_dist && e->scene.obj[i].neg != 1)
			{
				min_dist = dist;
				*a = e->scene.id;
			}
		}
		i++;
	}
	return (min_dist);
}

t_ray			get_reflected_ray(t_rt *e, t_ray rayon, t_vec3 poi)
{
	t_vec3		normale;
	t_ray		ray;

	ray.pos = poi;
	normale = object_norm(e->scene.obj[e->scene.id],
		poi, e->scene.cam.pos);
	ray.dir = vec_add3(vec_scale3(normale,
		(-2 * vec_dot3(rayon.dir, normale))), rayon.dir);
	return (ray);
}
