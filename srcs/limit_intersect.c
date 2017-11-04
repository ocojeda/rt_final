/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:18:58 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 20:20:20 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

float			get_res_of_limit_quadratic(t_calc *op)
{
	op->disc = op->b * op->b - 4 * op->a * op->c;
	if (op->disc < 0)
		return (DIST_MAX);
	if (op->disc == 0)
		return (-op->b / (2 * op->a));
	op->disc = sqrt(op->disc);
	op->t0 = (-op->b + op->disc) / (2 * op->a);
	op->t1 = (-op->b - op->disc) / (2 * op->a);
	if ((op->t0 < op->t1 || op->t1 < EPSILON) && op->t0 > EPSILON)
		return (op->t0);
	else if ((op->t1 < op->t0 || op->t0 < EPSILON) && op->t1 > EPSILON)
		return (op->t1);
	return (DIST_MAX);
}

float			intersect_limit_plane(t_ray ray, t_limit *plane, t_rt *e)
{
	float		d;
	float		dist;
	t_vec3		vector_distance;

	(void)e;
	if ((d = vec_dot3(plane->vector, ray.dir)) == 0)
		return (DIST_MAX);
	vector_distance = vec_sub3(plane->pos, ray.pos);
	dist = vec_dot3(vector_distance, plane->vector) / d;
	if (dist <= 0)
		return (DIST_MAX);
	return (dist);
}

t_vec3			norm_limit_plane(t_limit *plane, t_ray ray)
{
	float		d;
	float		dist;
	t_vec3		vector_distance;

	if ((d = vec_dot3(ray.dir, plane->vector)) == 0)
		return (vec_inv3(plane->vector));
	vector_distance = vec_sub3(ray.pos, plane->pos);
	dist = vec_dot3(vector_distance, ray.dir) / d;
	if (dist <= 0)
		return (vec_inv3(plane->vector));
	return (plane->vector);
}

float			intersect_limit_sphere(t_ray ray, t_limit *sphere)
{
	t_vec3		x;
	t_calc		op;

	ray.dir = vec_norme3(ray.dir);
	x = vec_sub3(ray.pos, sphere->pos);
	op.a = vec_dot3(ray.dir, ray.dir);
	op.b = 2 * vec_dot3(ray.dir, x);
	op.c = vec_dot3(x, x) - (sphere->r * sphere->r);
	op.eq = get_res_of_limit_quadratic(&op);
	return (op.eq);
}

float			intersect_obj_limit(t_ray ray, t_limit *obj, t_rt *e)
{
	(void)ray;
	(void)obj;
	(void)e;
	if (obj->type == SPHERE)
		return (intersect_limit_sphere(ray, obj));
	if (obj->type == PLANE)
		return (intersect_limit_plane(ray, obj, e));
	return (DIST_MAX);
}
