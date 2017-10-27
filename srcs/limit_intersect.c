#include "../includes/rt.h"

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

float			intersect_obj_limit(t_ray ray, t_limit *obj, t_rt *e)
{
    (void)ray;
    (void)obj;
    (void)e;
/*	if (obj->type == CYLINDER)
		return (intersect_limit_cylinder(ray, obj), e, ray));
*/	if (obj->type == SPHERE)
		return (intersect_limit_sphere(ray, obj));
	if (obj->type == PLANE)
		return (intersect_limit_plane(ray, obj, e));
/*	else if (obj->type == CONE)
		return (intersect_limit_cone(ray, obj), e, ray));
	else if (obj->type == PARABOLOID)
		return (intersect_limit_paraboloid(ray, obj), e, ray));
*/	return (DIST_MAX);
}