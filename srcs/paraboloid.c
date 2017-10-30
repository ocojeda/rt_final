#include "../includes/rt.h"

t_vec3			paraboloid_norm(t_obj parabol, t_vec3 poi)
{
    t_vec3		normal;
	t_vec3		tmp;
	t_vec3		project;
	float		dot;

	tmp = vec_sub3(poi, parabol.pos);
    dot = vec_dot3(tmp, parabol.vector);
    dot = dot + parabol.k;
	project = vec_scale3(parabol.vector, dot);
	normal = vec_sub3(tmp, project);
	return (vec_norme3(normal));
}

float			intersect_paraboloid(t_ray ray, t_obj *parab)
{
	t_calc		op;
	t_vec3		x;
	float		dotdv;
	float		dotxv;

	x = vec_sub3(ray.pos, parab->pos);
	dotdv = vec_dot3(ray.dir, parab->vector);
	dotxv = vec_dot3(x, parab->vector);
	op.a = vec_dot3(ray.dir, ray.dir) - p(dotdv);
	op.b = 2 * (vec_dot3(ray.dir, x) - (dotdv * (vec_dot3(x, parab->vector) + 2 * parab->k)));
	op.c = vec_dot3(x, x) - dotxv * ( vec_dot3(x, parab->vector) + 4 * parab->k);
	op.eq = get_res_of_quadratic(&op, parab);
    return (op.eq);
}

float			intersect_paraboloid_neg(t_ray ray, t_obj *parab, float dist_obj, float max_dist)
{
	t_calc		op;
	t_vec3		x;
	float		dotdv;
	float		dotxv;

	x = vec_sub3(ray.pos, parab->pos);
	dotdv = vec_dot3(ray.dir, parab->vector);
	dotxv = vec_dot3(x, parab->vector);
	op.a = vec_dot3(ray.dir, ray.dir) - p(dotdv);
	op.b = 2 * (vec_dot3(ray.dir, x) - (dotdv * (vec_dot3(x, parab->vector) + 2 * parab->k)));
	op.c = vec_dot3(x, x) - dotxv * ( vec_dot3(x, parab->vector) + 4 * parab->k);
	op.eq = get_res_of_quadratic_neg(&op, parab, dist_obj, max_dist);
    return (op.eq);
}