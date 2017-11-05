/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:14:01 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/05 00:03:48 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

float		intersect_cone_neg(t_ray ray, t_obj *cone,
	float dist_obj, float max_dist)
{
	t_calc		op;
	t_vec3		x;
	float		dotdv;
	float		dotxv;

	x = vec_sub3(ray.pos, cone->pos);
	dotdv = vec_dot3(ray.dir, cone->vector);
	dotxv = vec_dot3(x, cone->vector);
	op.a = vec_dot3(ray.dir, ray.dir) - (1 + p(cone->k)) * p(dotdv);
	op.b = 2 * (vec_dot3(ray.dir, x) - (1 + p(cone->k)) * dotdv * dotxv);
	op.c = vec_dot3(x, x) - (1 + p(cone->k)) * p(dotxv);
	op.eq = get_res_of_quadratic_neg(&op, cone, dist_obj, max_dist);
	return (op.eq);
}

float		intersect_sphere_neg(t_ray ray, t_obj *sphere,
	float dist_obj, float max_dist)
{
	t_vec3		x;
	t_calc		op;

	ray.dir = vec_norme3(ray.dir);
	x = vec_sub3(ray.pos, sphere->pos);
	op.a = vec_dot3(ray.dir, ray.dir);
	op.b = 2 * vec_dot3(ray.dir, x);
	op.c = vec_dot3(x, x) - (sphere->r * sphere->r);
	op.eq = get_res_of_quadratic_neg(&op, sphere, dist_obj, max_dist);
	return (op.eq);
}

float		intersect_paraboloid_neg(t_ray ray,
	t_obj *parab, float dist_obj, float max_dist)
{
	t_calc		op;
	t_vec3		x;
	float		dotdv;
	float		dotxv;

	x = vec_sub3(ray.pos, parab->pos);
	dotdv = vec_dot3(ray.dir, parab->vector);
	dotxv = vec_dot3(x, parab->vector);
	op.a = vec_dot3(ray.dir, ray.dir) - p(dotdv);
	op.b = 2 * (vec_dot3(ray.dir, x) - (dotdv *
		(vec_dot3(x, parab->vector) + 2 * parab->k)));
	op.c = vec_dot3(x, x) - dotxv *
		(vec_dot3(x, parab->vector) + 4 * parab->k);
	op.eq = get_res_of_quadratic_neg(&op, parab, dist_obj, max_dist);
	return (op.eq);
}

float		intersect_cylinder_neg(t_ray ray, t_obj *cyl,
	float dist_obj, float max_dist)
{
	t_calc	op;
	float	dotdv;
	float	dotxv;
	t_vec3	x;

	x = vec_sub3(ray.pos, cyl->pos);
	dotdv = vec_dot3(ray.dir, cyl->vector);
	dotxv = vec_dot3(x, cyl->vector);
	op.a = vec_dot3(ray.dir, ray.dir) - p(dotdv);
	op.b = 2 * (vec_dot3(ray.dir, x) - dotdv * dotxv);
	op.c = vec_dot3(x, x) - p(dotxv) - p(cyl->r);
	op.eq = get_res_of_quadratic_neg(&op, cyl, dist_obj, max_dist);
	return (op.eq);
}

float		check_negative_objects(float dist_obj,
	t_rt *e, t_ray ray, float max_dist)
{
	int		i;
	float	dist;

	i = 0;
	dist = dist_obj;
	while (i++ <= e->scene.nbr_obj)
	{
		if (e->scene.obj[i].neg == 1)
		{
			if (e->scene.obj[i].type == CYLINDER)
				dist = intersect_cylinder_neg(ray,
					&e->scene.obj[i], dist_obj, max_dist);
			else if (e->scene.obj[i].type == SPHERE)
				dist = intersect_sphere_neg(ray,
					&e->scene.obj[i], dist_obj, max_dist);
			else if (e->scene.obj[i].type == CONE)
				dist = intersect_cone_neg(ray,
					&e->scene.obj[i], dist_obj, max_dist);
			else if (e->scene.obj[i].type == PARABOLOID)
				dist = intersect_paraboloid_neg(ray,
					&e->scene.obj[i], dist_obj, max_dist);
		}
	}
	return (dist);
}
