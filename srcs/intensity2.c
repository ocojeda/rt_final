#include "../includes/rt.h"

int				set_isnt_in_shadow(t_light *light, t_reflect *ref, t_vec3 poi)
{
	light->ray.dir = vec_sub3(light->ray.pos, poi);
	ref->total_distance = get_length(light->ray.dir);
	light->ray.dir = vec_norme3(light->ray.dir);
	ref->ray = c_ray(vec_add3(poi, light->ray.dir), light->ray.dir);
	return (1);
}