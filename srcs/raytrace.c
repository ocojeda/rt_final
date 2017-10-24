#include "../includes/rt.h"

float			check_negative_objects(float dist_obj, t_rt *e, t_ray ray)
{
	int i;

	i = 0;
	while (i++ <= e->scene.nbr_obj -1)
	if (e->scene.obj[i].neg == 1)
	{
		if (e->scene.obj[i].type == CYLINDER)
			return(intersect_cylinder_neg(ray, &e->scene.obj[i] , dist_obj));
		else if (e->scene.obj[i].type == SPHERE)
			return (intersect_sphere_neg(ray, &e->scene.obj[i], dist_obj));
		else if (e->scene.obj[i].type == CONE)
			return (intersect_cone_neg(ray, &e->scene.obj[i],dist_obj));
	}
	return (dist_obj);
}

float			intersect_obj(t_ray ray, t_obj *obj, t_rt *e)
{
	if (obj->type == CYLINDER)
		return (check_negative_objects(intersect_cylinder(ray, obj), e, ray));
	else if (obj->type == SPHERE)
		return (check_negative_objects(intersect_sphere(ray, obj), e, ray));
	else if (obj->type == PLANE)
		return (check_negative_objects(intersect_plane(ray, obj), e, ray));
	else if (obj->type == CONE)
		return (check_negative_objects(intersect_cone(ray, obj), e, ray));
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
		return (color_mult(obj.color, intensity, 1));
	return ((t_color){0, 0, 0, 0});
}

float			get_min_dist(t_rt *e, t_ray ray)
{
	float		min_dist;
	float		dist;
	int			i;

	i = 0;
	dist = DIST_MAX;
	min_dist = DIST_MAX;
	while (i < e->scene.nbr_obj)
	{
		dist = intersect_obj(ray, &e->scene.obj[i], e);
		if (dist < min_dist && e->scene.obj[i].neg != 1)
		{
			min_dist = (dist < 0) ? min_dist : dist;
			e->scene.id = i;
		}
		i++;
	}
	return ((min_dist < DIST_MAX) ? min_dist : -1);
}

t_ray			get_refracted_ray(t_rt *e, t_ray rayon, t_vec3 poi)
{
	t_vec3		source;
	t_vec3		normale;
	t_ray		ray;

	ray.pos = poi;
	normale = color_norm(e->scene.obj[e->scene.id], poi,
						vec_sub3(CCAM.pos, poi));
	source = rayon.dir;
	ray.dir = vec_scale3(vec_mul3(source, normale),
	e->scene.obj[e->scene.id].mat.refract);
	ray.dir = vec_mul3(ray.dir, normale);
	ray.dir = vec_norme3(vec_sub3(vec_scale3(source,
	e->scene.obj[e->scene.id].mat.refract + 1), ray.dir));
	return (ray);
}

static t_color	g_norme2(t_rt *e, t_norme n, t_color base_color,
t_reflect ref)
{
	if (e->scene.obj[n.a].mat.reflex == 1)
		return (get_reflected_color(e, n.newpoi, base_color, ref));
	n.distance_rate *= e->scene.obj[n.a].mat.reflex;
	n.temp_color1 = get_reflected_color(e, n.newpoi, base_color, ref);
	return (ft_map_color(base_color, n.temp_color1, n.distance_rate));
	return (base_color);
}

static void		g_norme(t_rt *e, t_reflect *ref, t_norme *n, t_vec3 poi)
{
	ref->counter--;
	ref->new_ray = get_refracted_ray(e, ref->ray, poi);
	n->taux_temp = e->scene.obj[e->scene.id].mat.refract;
	ref->min_dist = find_min_dist_for_refref(e, &n->a, ref->new_ray);
	ref->total_distance += ref->min_dist;
	n->distance_rate = ft_map(ref->min_dist, ref->total_distance, 0, 1)
		* n->taux_temp;
}

void			prepare_refraction(t_rt *e, t_color *base_color,
		t_norme *n, t_reflect *ref)
{
	n->newpoi = vec_add3(ref->new_ray.pos, vec_scale3(ref->new_ray.dir,
	ref->min_dist));
	n->final_color = get_color(e, e->scene.obj[n->a], n->newpoi);
	*base_color = ft_map_color(*base_color, n->final_color, n->taux_temp);
	e->scene.id = n->a;
}


t_color			get_refracted_color(t_rt *e, t_vec3 poi, t_color base_color,
	t_reflect ref)
{
		t_norme		n;
	
		if (ref.counter == 0)
			return (base_color);
		g_norme(e, &ref, &n, poi);
		if (ref.min_dist < DIST_MAX)
		{
			prepare_refraction(e, &base_color, &n, &ref);
			ref.ray = c_ray(poi, ref.new_ray.dir);
			if (e->scene.obj[n.a].mat.refract)
			{
				n.distance_rate *= e->scene.obj[n.a].mat.refract;
				n.temp_color1 = get_refracted_color(e, n.newpoi, base_color, ref);
				return (ft_map_color(base_color, n.temp_color1, n.distance_rate));
			}
			else if (e->scene.obj[n.a].mat.reflex)
				base_color = g_norme2(e, n, base_color, ref);
			return (base_color);
		}
		return (ft_map_color(base_color, c_color(0,0,0), n.taux_temp));
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
	if (e->scene.obj[e->scene.id].mat.reflex)
		return (ret_reflected_pixel(e, ref, ray, ref.total_distance));
	if (e->scene.obj[e->scene.id].mat.refract)
	{
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi);
		e->scene.id = ref.tmp_id;
		return (get_refracted_color(e, ref.poi, ref.color, ref));
	}
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
