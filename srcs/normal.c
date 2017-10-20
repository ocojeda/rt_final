#include "rtv1.h"

t_vec3			color_norm(t_obj obj, t_vec3 poi, t_vec3 cam)
{
	t_vec3	norm;

	norm = object_norm(obj, poi);
	if (obj.nbr_t == 1 && vec_dot3(norm, cam) < 0)
		norm = vec_scale3(norm, -1);
	return (norm);
}

t_vec3			object_norm(t_obj obj, t_vec3 poi)
{
	t_vec3	norm;

	norm = vec_new3(0, 0, 0);
	if (obj.type == CYLINDER)
		norm = vec_norme3(cylinder_norm(obj, poi));
	else if (obj.type == SPHERE)
		norm = vec_norme3(sphere_norm(obj, poi));
	else if (obj.type == PLANE)
		norm = vec_norme3(plane_norm(obj));
	else if (obj.type == CONE)
		norm = vec_norme3(cone_norm(obj, poi));
	return (norm);
}