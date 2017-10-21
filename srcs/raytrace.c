#include "rtv1.h"

float			intersect_obj(t_ray ray, t_obj *obj)
{
	if (obj->type == CYLINDER)
		return (intersect_cylinder(ray, obj));
	if (obj->type == SPHERE)
		return (intersect_sphere(ray, obj));
	else if (obj->type == PLANE)
		return (intersect_plane(ray, obj));
	else if (obj->type == CONE)
		return (intersect_cone(ray, obj));
	return (DIST_MAX);
}

float			get_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_color			get_color(t_rt *e, t_obj obj, t_vec3 poi)
{
	float		intensity;
	int			i;

	i = -1;
	intensity = (!e->scene.nbr_light) ? AMBIENT_LIGHT : 0;
	while (++i < e->scene.nbr_light)
		intensity += intensity_obj(e, poi, obj, e->CLIGHT) ;
	if (intensity != 0)
	{
		return (color_mult(obj.color, intensity, 1));
	}
	return ((t_color){0, 0, 0, 0});
}

float			get_min_dist(t_rt *e, t_ray ray)
{
	float		min_dist;
	float		dist;
	int			i;

	(void)ray;
	i = 0;
	dist = DIST_MAX;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		dist = intersect_obj(ray, &e->scene.obj[i]);
		if (dist < min_dist)
		{
			min_dist = (dist < 0) ? min_dist : dist;
			e->scene.id = i;
		}
		i++;
	}
	return ((min_dist < DIST_MAX) ? min_dist : -1);
}

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
			dist = intersect_obj(ray, &e->scene.obj[i]);
			if (dist < min_dist)
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
//	if (e->scene.obj[ref.a].mat.reflex == 1)
		return (get_reflected_color(e, ref.poi, base_color, ref));
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
						poi, vec_sub3(e->scene.cam.pos, poi)));
	temp_rate = e->scene.obj[e->scene.id].mat.reflex;
	ref.min_dist = find_min_dist_for_refref(e, &a, ref.new_ray);
	ref.total_distance = ref.total_distance + ref.min_dist;
	if (ref.min_dist < DIST_MAX)
		return (add_refref_colors(e, a, base_color, ref));
	return (base_color);
}

t_color			ret_reflected_pixel(t_rt *e, t_reflect ref, t_ray ray,
	float min_dist)
{
	(void)min_dist;
	(void)ray;
	ref.color = color_mult(get_color(e, e->scene.obj[e->scene.id], ref.poi), 1-e->scene.obj[ref.tmp_id].mat.reflex, 1);
	e->scene.id = ref.tmp_id;
	ref.color = ft_map_color(ref.color,
	get_reflected_color(e, ref.poi, ref.color, ref),
		e->scene.obj[ref.tmp_id].mat.reflex);
	e->scene.id = ref.tmp_id;
	return (ref.color);
}

static t_color	get_pxl_color(t_rt *e, t_ray ray)
{
	t_reflect	ref;

	e->scene.id = -1;
	if ((ref.min_dist = get_min_dist(e, ray)) == -1)
		return (c_color(0,0,0)); // a ajouter ici la skybox
	ref.tmp_id = e->scene.id;
	ref.poi = vec_add3(ray.pos, vec_scale3(ray.dir, ref.min_dist));
	ref.counter = NR_ITER;
	ref.ray = c_ray(ray.pos, ray.dir);
	ref.total_distance = ref.min_dist;
	ref.tmp_id = e->scene.id;
	if (e->scene.obj[e->scene.id].mat.reflex)
		return (ret_reflected_pixel(e, ref, ray, 0));
//		if (CMAT.refract)
//		{
//			ref.color = get_color(e, CID, ref.poi);
//			e->scene.id = ref.tmp_id;
//			return (get_refracted_color(e, ref.poi, ref.color, ref));
//		}
//		if (CMAT.checker.l > 0)
//			return (get_checker_col(CMAT.checker, ref.poi));
//		return (get_color(e, CID, ref.poi));
//	}
	/*printf("%f ",ray.dir.x);
	printf("%f ",ray.dir.y);
	printf("%f ",ray.dir.z);
	ft_putchar('\n');*/
	//ft_putnbr((int)e->scene.obj[1].color.r);
	//ref.color = c_color(e->scene.obj[e->scene.id].color.r, e->scene.obj[e->scene.id].color.g, e->scene.obj[e->scene.id].color.b);
	ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi);
	return (ref.color);
}

t_color			raytrace(int x, int y, t_rt *e)
{
	t_color		color;
	t_ray		ray;

	ray = ray_init(e, x * RES / ALIASING, y * RES / ALIASING);
	color = get_pxl_color(e, ray);
	return (color);
}