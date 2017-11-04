#include "../includes/rt.h"


float			find_min_dist_for_refref(t_rt *e, int *a, t_ray ray)
{
	float		min_dist;
	float		dist;
	// t_ray		ray2;
	int			i;
	// t_vec3 		pos_tmp;
	// t_vec3		new_poi;

	i = 0;
	dist = 0;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
	/*	if (i == e->scene.id && e->scene.obj[i].mat.damier == 1 && e->scene.obj[i].type == SPHERE)
		{
			dist = intersect_obj(ray, &e->scene.obj[i], e);
			if (dist < min_dist && e->scene.obj[i].neg != 1)
			{
				new_poi = vec_add3(ray.pos, vec_scale3(ray.dir, dist));
				pos_tmp = vec_sub3(new_poi, e->scene.obj[i].pos);;
				if((damier(&pos_tmp, e)))
				{
					min_dist = dist;
					*a = i;
				}
			}
		}
	*/	if (i != e->scene.id)
		{
			dist = intersect_obj(ray, &e->scene.obj[i], e);
			if (dist < min_dist && e->scene.obj[i].neg != 1)
			{
				min_dist = dist;
				*a = i;
			}
		}
		i++;
	}
	return (min_dist);
}

t_ray			get_reflected_ray(t_rt *e, t_ray rayon, t_vec3 poi)
{
	t_vec3		normale;
	t_ray		ray;

	ray.pos = poi;
	normale = object_norm(e->scene.obj[e->scene.id], poi, e->scene.cam.pos, rayon);
	ray.dir = vec_add3(vec_scale3(normale, (-2 * vec_dot3(rayon.dir, normale))), rayon.dir);
	return (ray);
}