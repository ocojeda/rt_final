#include "../includes/rt.h"


float			intersect_cone_neg(t_ray ray, t_obj *cone, float dist_obj)
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
	op.eq = get_res_of_quadratic_neg(&op, cone, dist_obj);
	//if (op.eq == op.t0)
	//	return (limit_dist(*cone, ray, op.eq, op.t1));
	//else
	//	return (limit_dist(*cone, ray, op.eq, op.t0));
    return (op.eq);
}

float			intersect_sphere_neg(t_ray ray, t_obj *sphere, float dist_obj)
{
	t_vec3		x;
	t_calc		op;

	ray.dir = vec_norme3(ray.dir);
	x = vec_sub3(ray.pos, sphere->pos);
	op.a = vec_dot3(ray.dir, ray.dir);
	op.b = 2 * vec_dot3(ray.dir, x);
	op.c = vec_dot3(x, x) - (sphere->r * sphere->r);
	op.eq = get_res_of_quadratic_neg(&op, sphere, dist_obj);
	return (op.eq);
}

float		intersect_cylinder_neg(t_ray ray, t_obj *cyl, float dist_obj)
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
	op.eq = get_res_of_quadratic_neg(&op, cyl, dist_obj);
    return (op.eq);
}

float			check_negative_objects(float dist_obj, t_rt *e, t_ray ray)
{
	int i;

	i = 0;
	while (i++ <= e->scene.nbr_obj -1)
	if (e->scene.obj[i].neg == 1)
	{
		if (e->scene.obj[i].type == CYLINDER)
			return(intersect_cylinder_neg(ray, &e->scene.obj[i] , dist_obj));
		else if (e->scene.obj[i].type == SPHERE)
			return (intersect_sphere_neg(ray, &e->scene.obj[i], dist_obj));
		else if (e->scene.obj[i].type == CONE)
			return (intersect_cone_neg(ray, &e->scene.obj[i],dist_obj));
		else if (e->scene.obj[i].type == PARABOLOID)
			return (intersect_paraboloid_neg(ray, &e->scene.obj[i],dist_obj));
	}
	return (dist_obj);
}
