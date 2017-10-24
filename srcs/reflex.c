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

t_color			recursive_refref(t_rt *e, t_color base_color, t_reflect ref)
{
	t_color color1;
	if (e->scene.obj[ref.a].mat.reflex)
	{
		if (e->scene.obj[ref.a].mat.reflex == 1)
			return (get_reflected_color(e, ref.poi, base_color, ref));
		ref.dist_rate *= e->scene.obj[ref.a].mat.reflex;
		color1 = get_reflected_color(e, ref.poi, base_color, ref);
		return (ft_map_color(base_color, color1, ref.dist_rate));
	}
	return base_color;
}

t_color			add_refref_colors(t_rt *e, int a, t_color base_color,
	t_reflect ref)
{
	t_vec3		point_of_impact;
	t_color		final_color;
	float		temp_rate;
	float		distance_rate;
	

	distance_rate = ft_map(ref.min_dist, ref.total_distance, 0, 1);
	temp_rate = e->scene.obj[e->scene.id].mat.reflex;
	point_of_impact = vec_add3(ref.ray.pos, vec_scale3(ref.ray.dir,
	ref.min_dist));
	final_color = get_color(e, e->scene.obj[a], point_of_impact);
	base_color = ft_map_color(base_color, final_color, temp_rate);
	e->scene.id = a;
	ref.a = a;
	ref.ray = c_ray(point_of_impact, ref.new_ray.dir);
	ref.poi = vec_scale3(point_of_impact, 1);
	ref.dist_rate = distance_rate;
	if (e->scene.obj[a].mat.reflex)
		return (recursive_refref(e, base_color, ref));
	return (base_color);
}

t_color			get_reflected_color(t_rt *e, t_vec3 poi,
	t_color base_color, t_reflect ref)
{
	int			a;
	float		temp_rate;

	if (ref.counter == 0)
	return (base_color);
	ref.counter--;
	ref.new_ray = c_ray(poi, color_norm(e->scene.obj[e->scene.id],
					poi, vec_sub3(CCAM.pos, poi)));
	temp_rate = e->scene.obj[e->scene.id].mat.reflex;
	ref.min_dist = find_min_dist_for_refref(e, &a, ref.new_ray);
	ref.total_distance = ref.total_distance + ref.min_dist;
	if (ref.min_dist < DIST_MAX)
		return (add_refref_colors(e, a, base_color, ref));
	return (ft_map_color(base_color, c_color(0,0,0), temp_rate));
}

t_color			ret_reflected_pixel(t_rt *e, t_reflect ref, t_ray ray,
	float min_dist)
{
	(void)ray;
	(void)min_dist;
	ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi);
	e->scene.id = ref.tmp_id;
	
	ref.color = ft_map_color(ref.color,
	get_reflected_color(e, ref.poi, ref.color, ref),e->scene.obj[ref.tmp_id].mat.reflex);
	e->scene.id = ref.tmp_id;
	/*	if (e->scene.obj[e->scene.id].mat.refract)
		{
			ref.counter = NR_ITER;
			ref.ray = c_ray(ray.pos, ray.dir);
			ref.total_distance = 0;
			ref.poi = vec_add3(ray.pos, vec_scale3(ray.dir, min_dist));
			ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi);
			e->scene.id = ref.tmp_id;
			temp_color = copy_color(ref.color);
			return (ft_map_color(temp_color, get_refracted_color(e, ref.poi,
				ref.color, ref), 1 - e->scene.obj[e->scene.id].mat.refract));
		}*/
	return (ref.color);
}