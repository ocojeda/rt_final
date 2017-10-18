#include "rtv1.h"

float			get_res_of_quadratic(t_calc *op, t_obj *obj)
{
	op->disc = op->b * op->b - 4 * op->a * op->c;
	if (op->disc < 0)
		return (DIST_MAX);
	obj->nbr_t = (op->disc == 0) ? 1 : 2;
	if (op->disc == 0)
		return (-op->b / (2 * op->a));
	op->disc = sqrt(op->disc);
	op->t0 = (-op->b + op->disc) / (2 * op->a);
	op->t1 = (-op->b - op->disc) / (2 * op->a);
	if (op->t0 <= 0 || op->t1 <= 0)
		obj->nbr_t = 1;
	if ((op->t0 < op->t1 || op->t1 < EPSILON) && op->t0 > EPSILON)
		return (op->t0);
	else if ((op->t1 < op->t0 || op->t0 < EPSILON) && op->t1 > EPSILON)
		return (op->t1);
	return (DIST_MAX);
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