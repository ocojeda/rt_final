/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:20:54 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:28:23 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

float			limit_obj(t_ray ray, t_obj *obj, float dist, t_rt *e)
{
	int			u;
	float		dist2;
	t_vec3		norm;
	t_ray		poi;

	u = 0;
	poi = c_ray(vec_add3(ray.pos, vec_scale3(ray.dir, dist)),
		vec_new3(0, 0, 0));
	while (u < obj->limit_nbr && (dist != DIST_MAX && dist != dist2))
	{
		poi.dir = vec_norme3(vec_sub3(obj->limit[u].pos, poi.pos));
		dist2 = intersect_obj_limit(ray, &obj->limit[u], e);
		norm = norm_limit_plane(&obj->limit[u], poi);
		if (!((norm.x == (obj->limit[u].vector.x * -1) && norm.y ==
		(obj->limit[u].vector.y * -1) && norm.z ==
		(obj->limit[u].vector.z * -1)) || dist == DIST_MAX))
			dist = (norm.x == (obj->limit[u].vector.x) && norm.y ==
(obj->limit[u].vector.y) && norm.z == (obj->limit[u].vector.z) && dist2 <
obj->max_dist && dist2 < DIST_MAX && dist <= dist2) ? dist2 : DIST_MAX;
		u++;
	}
	return (dist);
}

float			intersect_obj(t_ray ray, t_obj *obj, t_rt *e)
{
	float dist;

	dist = DIST_MAX;
	if (obj->type == CYLINDER)
		dist = check_negative_objects(
			intersect_cylinder(ray, obj), e, ray, obj->max_dist);
	else if (obj->type == SPHERE)
		dist = check_negative_objects(
			intersect_sphere(ray, obj), e, ray, obj->max_dist);
	else if (obj->type == PLANE)
		dist = check_negative_objects(
			intersect_plane(ray, obj), e, ray, obj->max_dist);
	else if (obj->type == CONE)
		dist = check_negative_objects(
			intersect_cone(ray, obj), e, ray, obj->max_dist);
	else if (obj->type == PARABOLOID)
		dist = check_negative_objects(
			intersect_paraboloid(ray, obj), e, ray, obj->max_dist);
	if (obj->limit_active == 1 && dist != DIST_MAX)
		return (limit_obj(ray, obj, dist, e));
	return (dist);
}

float			get_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float			get_min_dist(t_rt *e, t_ray ray)
{
	float		min_dist;
	float		dist;
	int			i;

	i = 0;
	dist = DIST_MAX;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		dist = intersect_obj(ray, &e->scene.obj[i], e);
		if (dist < min_dist && e->scene.obj[i].neg != 1)
		{
			min_dist = (dist < 0) ? min_dist : dist;
			e->scene.id = i;
		}
		i++;
	}
	return ((min_dist < DIST_MAX) ? min_dist : -1);
}
