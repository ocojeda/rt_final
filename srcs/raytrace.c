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

t_color			get_text_color(int x, int y, t_texture tex)
{
	int			c;
	t_color		color;
	int			pos;

	if (x < tex.width && y < tex.height && x >= 0 && y >= 0)
	{
		pos = (x * tex.bpp / 8) + (y * tex.sizl);
		c = *(int*)&(tex.data[pos]);
		color.r = c / 65536 % 256;
		color.g = c / 256 % 256;
		color.b = c % 256;
		return (color);
	}
	return ((t_color){0, 0, 0, 0});
}

t_color			skybox(t_rt *e, t_ray ray)
{
	t_color		color_sky;
	t_vec2		uv;
	t_vec3		norm;
	int			i;
	float		intensity;

	i = -1;
	intensity = 0;
	color_sky = (t_color){0, 0, 0, 0};
	//while (++i < e->scene.nbr_light)
	//	intensity += dazzling_light(e, e->CLIGHT, vec_norme3(ray.dir));
	//while (++i < e->scene.nbr_light)
	//	intensity = 1;
	//if (!(e->scene.skybox.is_init))
	//	return (color_mult((t_color){0, 0, 0, 0}, intensity, 0));
	norm = vec_norme3(ray.dir);
	uv.x = atan2(norm.x, norm.z) / (2 * M_PI) + 0.5;
	uv.y = norm.y * 0.5 + 0.5;
	uv.x = e->scene.skybox.width * (1 - uv.x);
	uv.y = e->scene.skybox.height * (1 - uv.y);
	return(color_sky = get_text_color((int)uv.x, (int)uv.y, e->scene.skybox));
	//intensity *= (color_is_black(&color_sky)) ? 100 : 5;
	return (color_mult(color_sky, 1 + intensity, 0));
}

t_color	get_pxl_color(t_rt *e, t_ray ray)
{
	t_reflect	ref;

	e->scene.id = -1;
	if ((ref.min_dist = get_min_dist(e, ray)) == -1)
		return (c_color(0,0,0)); // a ajouter ici la skybox
	ref.type = e->scene.obj[e->scene.id].type;
	ref.tmp_id = e->scene.id;
	ref.poi = vec_add3(ray.pos, vec_scale3(ray.dir, ref.min_dist));
	ref.counter = NR_ITER;
	ref.ray = c_ray(ray.pos, ray.dir);
	ref.total_distance = ref.min_dist;
	if (e->scene.obj[e->scene.id].mat.reflex)
	{
		ref.color = get_color(e, e->scene.obj[e->scene.id], ref.poi);
		e->scene.id = ref.tmp_id;
		return (get_refracted_color(e, ref.poi, ref.color, ref));
	}
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
	return (skybox(e, ray));
	return (color);
}
