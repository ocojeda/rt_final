#include "../includes/rt.h"

t_vec3			color_norm(t_obj obj, t_vec3 poi, t_vec3 cam)
{
	t_vec3	norm;

	norm = object_norm(obj, poi, cam);
	//if ((vec_dot3(norm, cam) < 0) && obj.type == PLANE)
	//	norm = vec_inv3(norm);
	return (norm);
}

t_vec3			object_norm(t_obj obj, t_vec3 poi, t_vec3 cam)
{
	t_vec3	norm;

	cam.x = cam.x;
	norm = vec_new3(0, 0, 0);
	if (obj.type == CYLINDER)
		norm = vec_norme3(cylinder_norm(obj, poi));
	else if (obj.type == SPHERE)
		norm = vec_norme3(sphere_norm(obj, poi));
	else if (obj.type == PLANE)
		norm = vec_norme3(plane_norm(obj));
	else if (obj.type == CONE)
		norm = vec_norme3(cone_norm(obj, poi));
	else if (obj.type == PARABOLOID)
		norm = vec_norme3(paraboloid_norm(obj, poi));
	return (norm);
}
