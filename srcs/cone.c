#include "../includes/rt.h"

t_vec3			cone_norm(t_obj cone, t_vec3 poi)
{
	t_vec3		normal;
	t_vec3		tmp;
	t_vec3		project;
	float		dot;

	tmp = vec_sub3(poi, cone.pos);
	dot = vec_dot3(tmp, cone.vector);
	project = vec_scale3(cone.vector, dot);
	normal = vec_sub3(tmp, project);
	/*if (cone.mat.sin == 1)
	{
		normal.x = normal.x;
		normal.y = sin(normal.y) * 20;
		normal.z = normal.z;
	}*/
	return (vec_norme3(normal));
}

float			intersect_cone(t_ray ray, t_obj *cone)
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
		op.eq = get_res_of_quadratic(&op, cone);
	//if (op.eq == op.t0)
	//	return (limit_dist(*cone, ray, op.eq, op.t1));
	//else
	//	return (limit_dist(*cone, ray, op.eq, op.t0));
	
    return (op.eq);
}

float			get_res_of_quadratic_neg(t_calc *op, t_obj *obj, float dist_obj, float max_dist)
{
	op->disc = op->b * op->b - 4 * op->a * op->c;
	if (op->disc < 0)
		return (dist_obj);
	obj->nbr_t = (op->disc == 0) ? 1 : 2;
	if (op->disc == 0)
		return (dist_obj);
	op->disc = sqrt(op->disc);
	op->t0 = (-op->b + op->disc) / (2 * op->a);
	op->t1 = (-op->b - op->disc) / (2 * op->a);
	if (op->t0 <= 0 || op->t1 <= 0)
		obj->nbr_t = 1;
	if ((dist_obj > op->t0 && dist_obj < op->t1) || (dist_obj > op->t1 && dist_obj < op->t0))
		return((op->t0 < max_dist && op->t1 < max_dist) ? max_dist : DIST_MAX);
	return (dist_obj);
}
