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
		else if (e->scene.obj[i].type == PARABOLOID)
			return (intersect_paraboloid_neg(ray, &e->scene.obj[i],dist_obj));
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
	else if (obj->type == PARABOLOID)
		return (check_negative_objects(intersect_paraboloid(ray, obj), e, ray));
	return (DIST_MAX);
}

float			get_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float rand_noise(int t)
{
    t = (t<<13) ^ t;
    t = (t * (t * t * 15731 + 789221) + 1376312589);
    return 1.0 - (t & 0x7fffffff) / 1073741824.0;
}

t_color			get_color(t_rt *e, t_obj obj, t_reflect ref, t_ray ray)
{
	float		intensity;
	int			i;
	t_color		color1;
	t_ray		ray_tmp;

	i = -1;
	intensity = (!e->scene.nbr_light) ? AMBIENT_LIGHT : 0;
	while (++i < e->scene.nbr_light)
		intensity += intensity_obj(e, ref.poi, ray, e->CLIGHT);
	
	if (intensity != 0)
	{
		float	dot = vec_dot3(ray.dir, ref.poi);
		
		ray_tmp = get_reflected_ray(e, ray, ref.poi);
		dot = vec_dot3(ray.dir, ref.poi);
	
		color1 = color_mult(obj.color, intensity, 1);
		if(e->scene.obj[e->scene.id].mat.sinus)
			return (bruit(dot, color1, e->scene.obj[e->scene.id].color, rand_noise(ref.x))); 
			//return(bruit2(rand_noise(ref.x), ref.color, e->scene.obj[e->scene.id].color, dot));
			//return(bruit3(dot*0.9, ref.x, ref.y, e));
		return	color1;
	}
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

t_color	get_pxl_color(t_rt *e, t_ray ray, int x, int y)
{
	t_reflect	ref;
	float		tmp;

	e->scene.id = -1;
	if ((ref.min_dist = get_min_dist(e, ray)) == -1)
		return (c_color(0,0,0)); // a ajouter ici la skybox
	ref.x = x;
	ref.y = y;
	ref.type = e->scene.obj[e->scene.id].type;
	ref.tmp_id = e->scene.id;
	ref.poi = vec_add3(ray.pos, vec_scale3(ray.dir, ref.min_dist));
	ref.counter = NR_ITER;
	ref.ray = c_ray(ray.pos, ray.dir);
	ref.total_distance = ref.min_dist;
	if (e->scene.obj[e->scene.id].mat.reflex == 1)
	{
		tmp = e->scene.obj[e->scene.id].mat.reflex_filter;
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref, ray);
		e->scene.id = ref.tmp_id;
		return (ft_map_color(get_refracted_color(e, ref.poi, ref.color, ref), ref.color, tmp));
	}
	else if (e->scene.obj[e->scene.id].mat.refract == 1)
	{
		tmp = e->scene.obj[e->scene.id].mat.refract_filter;
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref, ray);
		e->scene.id = ref.tmp_id;
		return (ft_map_color(get_refracted_color(e, ref.poi, ref.color, ref), ref.color, tmp));
	}
	else
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref, ray);
	return (ref.color);
}

t_color			raytrace(int x, int y, t_rt *e)
{
	t_color		color;
	t_ray		ray;

	ray = ray_init(e, x * RES / ALIASING, y * RES / ALIASING);
	color = get_pxl_color(e, ray, x, y);
	return (color);
}
