#include "../includes/rt.h"

t_vec3			plane_norm(t_obj plane, t_ray ray)
{
	float		d;
	float		dist;
	t_vec3		vector_distance;

	if ((d = vec_dot3(ray.dir, plane.vector)) == 0)
		return (vec_inv3(plane.vector));
	vector_distance = vec_sub3(ray.pos, plane.pos);
	dist = vec_dot3(vector_distance, ray.dir) / d;
	if (dist <= 0)
		return (vec_inv3(plane.vector));
	return (plane.vector);
}

float			intersect_plane(t_ray ray, t_obj *plane)
{
	float		d;
	float		dist;
	t_vec3		vector_distance;

	if ((d = vec_dot3(plane->vector, ray.dir)) == 0)
		return (DIST_MAX);
	vector_distance = vec_sub3(plane->pos, ray.pos);
	dist = vec_dot3(vector_distance, plane->vector) / d;
	if (dist <= 0)
		return (DIST_MAX);
	return (dist);
}
