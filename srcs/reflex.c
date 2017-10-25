#include "../includes/rt.h"


float			find_min_dist_for_refref(t_rt *e, int *a, t_ray ray)
{
	float		min_dist;
	float		dist;
	int			i;

	i = 0;
	dist = 0;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		if (i != e->scene.id)
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

	(void)rayon;
	ray.pos = poi;
	normale = color_norm(e->scene.obj[e->scene.id], poi, e->scene.cam.pos);
	ray.dir = normale;
	return (ray);
}