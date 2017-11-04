/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:56:42 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 19:57:06 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

float			get_res_of_quadratic(t_calc *op, t_obj *obj)
{
	(void)obj;
	op->disc = op->b * op->b - 4 * op->a * op->c;
	if (op->disc < 0)
		return (DIST_MAX);
	if (op->disc == 0)
		return (-op->b / (2 * op->a));
	op->disc = sqrt(op->disc);
	op->t0 = (-op->b + op->disc) / (2 * op->a);
	op->t1 = (-op->b - op->disc) / (2 * op->a);
	if ((op->t0 < op->t1 || op->t1 < EPSILON) && op->t0 > EPSILON)
	{
		obj->max_dist = op->t1;
		return (op->t0);
	}
	else if ((op->t1 < op->t0 || op->t0 < EPSILON) && op->t1 > EPSILON)
	{
		obj->max_dist = op->t0;
		return (op->t1);
	}
	return (DIST_MAX);
}

t_vec3			sphere_norm(t_obj obj, t_vec3 poi)
{
	t_vec3	norme;

	norme = vec_norme3(vec_sub3(poi, obj.pos));
	return (norme);
}

float			intersect_sphere(t_ray ray, t_obj *sphere)
{
	t_vec3		x;
	t_calc		op;

	ray.dir = vec_norme3(ray.dir);
	x = vec_sub3(ray.pos, sphere->pos);
	op.a = vec_dot3(ray.dir, ray.dir);
	op.b = 2 * vec_dot3(ray.dir, x);
	op.c = vec_dot3(x, x) - (sphere->r * sphere->r);
	op.eq = get_res_of_quadratic(&op, sphere);
	return (op.eq);
}
