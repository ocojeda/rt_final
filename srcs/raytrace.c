#include "../includes/rt.h"

float			check_negative_objects(float dist_obj, t_rt *e, t_ray ray, float max_dist)
{
	int i;

	i = 0;
	while (i++ <= e->scene.nbr_obj -1)
	if (e->scene.obj[i].neg == 1)
	{
		if (e->scene.obj[i].type == CYLINDER)
			return(intersect_cylinder_neg(ray, &e->scene.obj[i] , dist_obj, max_dist));
		else if (e->scene.obj[i].type == SPHERE)
			return (intersect_sphere_neg(ray, &e->scene.obj[i], dist_obj, max_dist));
		else if (e->scene.obj[i].type == CONE)
			return (intersect_cone_neg(ray, &e->scene.obj[i],dist_obj, max_dist));
		else if (e->scene.obj[i].type == PARABOLOID)
			return (intersect_paraboloid_neg(ray, &e->scene.obj[i],dist_obj, max_dist));
	}
	return (dist_obj);
}

float			intersect_obj(t_ray ray, t_obj *obj, t_rt *e)
{
	if (obj->type == CYLINDER)
		return (check_negative_objects(intersect_cylinder(ray, obj), e, ray, obj->max_dist));
	else if (obj->type == SPHERE)
		return (check_negative_objects(intersect_sphere(ray, obj), e, ray, obj->max_dist));
	else if (obj->type == PLANE)
		return (check_negative_objects(intersect_plane(ray, obj), e, ray, obj->max_dist));
	else if (obj->type == CONE)
		return (check_negative_objects(intersect_cone(ray, obj), e, ray, obj->max_dist));
	else if (obj->type == PARABOLOID)
		return (check_negative_objects(intersect_paraboloid(ray, obj), e, ray, obj->max_dist));
	return (DIST_MAX);
}

float			get_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_color			get_color(t_rt *e, t_obj obj, t_vec3 poi, t_ray ray)
{
	float		intensity;
	int			i;

	i = -1;
	intensity = (!e->scene.nbr_light) ? AMBIENT_LIGHT : 0;
	while (++i < e->scene.nbr_light)
		intensity += intensity_obj(e, poi, ray, e->CLIGHT);
	if (intensity != 0)
		return (color_mult(obj.color, intensity, 1));
	return ((t_color){0, 0, 0, 0});
}

float			get_min_dist(t_rt *e, t_ray ray)
{
	float		min_dist;
	float		dist;
	float		dist2;
	float		dist3;
	float		dist4;
	t_ray		poi;
	int			i;
	int			u;

	i = 0;
	u = 0;
	dist = DIST_MAX;
	dist2 = DIST_MAX;
	dist3 = DIST_MAX;
	dist3 = DIST_MAX;
	min_dist = DIST_MAX;
	
	while (i < e->scene.nbr_obj)
	{
		dist = intersect_obj(ray, &e->scene.obj[i], e);
		if(e->scene.obj[i].limit_active == 1 && dist != DIST_MAX)
		{
			poi = c_ray(vec_add3(ray.pos, vec_scale3(ray.dir, dist)), vec_new3(0,0,0));
			while(u < e->scene.obj[i].limit_nbr)
			{
				poi.dir = vec_norme3(vec_sub3(e->scene.obj[i].limit[u].pos, poi.pos));
				dist2 = intersect_obj_limit(poi, &e->scene.obj[i].limit[u], e);
				if (e->scene.obj[i].limit[u].type == SPHERE)
					e->scene.obj[i].limit[u].r += 1;
				else if (e->scene.obj[i].limit[u].type == PLANE)
					e->scene.obj[i].limit[u].pos = vec_add3(e->scene.obj[i].limit[u].pos, e->scene.obj[i].limit[u].vector);
				poi.dir = vec_norme3(vec_sub3(e->scene.obj[i].limit[u].pos, poi.pos));
				dist3 = intersect_obj_limit(poi, &e->scene.obj[i].limit[u], e);
				if (e->scene.obj[i].limit[u].type == SPHERE)
					e->scene.obj[i].limit[u].r -= 1;
				else if (e->scene.obj[i].limit[u].type == PLANE)
					e->scene.obj[i].limit[u].pos = vec_sub3(e->scene.obj[i].limit[u].pos, e->scene.obj[i].limit[u].vector);
				dist4 = intersect_obj_limit(ray, &e->scene.obj[i].limit[u], e);
				if (dist3 < dist2 && dist4 <= e->scene.obj[i].max_dist && dist4 < DIST_MAX && dist <= dist4)
					dist = dist4;
				else if (dist3 < dist2)
					dist = DIST_MAX;
				u++;
			}
		}
		if(dist < min_dist && e->scene.obj[i].neg != 1)
		{
			min_dist = (dist < 0) ? min_dist : dist;
			e->scene.id = i;
		}
		u = 0;
		i++;
	}
	return ((min_dist < DIST_MAX) ? min_dist : -1);
}

t_color	get_pxl_color(t_rt *e, t_ray ray)
{
	t_reflect	ref;

	e->scene.id = -1;
	if ((ref.min_dist = get_min_dist(e, ray)) == -1)
		//return (c_color(0,0,0)); // a ajouter ici la skybox
		return (skybox(e, ray));

	ref.type = e->scene.obj[e->scene.id].type;
	ref.tmp_id = e->scene.id;
	ref.poi = vec_add3(ray.pos, vec_scale3(ray.dir, ref.min_dist));
	ref.counter = NR_ITER;
	ref.ray = c_ray(ray.pos, ray.dir);
	ref.total_distance = ref.min_dist;
	if (e->scene.obj[e->scene.id].mat.reflex)
	{
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi, ray);
		e->scene.id = ref.tmp_id;
		return (get_refracted_color(e, ref.poi, ref.color, ref));
	}
	if (e->scene.obj[e->scene.id].mat.refract)
	{
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi, ray);
		e->scene.id = ref.tmp_id;
		return (get_refracted_color(e, ref.poi, ref.color, ref));
	}
	ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi, ray);

	return (ref.color);
}

t_color			raytrace(int x, int y, t_rt *e)
{
	t_color		color;
	t_ray		ray;

	ray = ray_init(e, x * RES / ALIASING, y * RES / ALIASING);
	color = get_pxl_color(e, ray);
//	return (skybox(e, ray));
	return (color);
}
