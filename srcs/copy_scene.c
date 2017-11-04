#include "../includes/rt.h"

void				copy_limits2(t_obj *copy)
{
	if (copy->mat.damier == 1)
	{
		copy->mat.refract = 1;
		copy->mat.refract_rate = 0.5;
		copy->mat.refract_filter = 0;
		copy->mat.sinus = 0;
		copy->mat.reflex = 0;
		copy->mat.reflex_filter = 0;
	}
}

void				copy_limits(t_obj *obj, t_obj *copy)
{
	int i;

	i = 0;
	if (obj->limit_active == 1)
	while (i < obj->limit_nbr)
	{
		copy->limit[i].type = obj->limit[i].type;
		copy->limit[i].pos = obj->limit[i].pos;
		copy->limit[i].vector = obj->limit[i].vector;
		copy->limit[i].r = obj->limit[i].r;
		i++;
	}
	copy->k = obj->k;
	copy->vector = obj->vector;
	copy->r = obj->r;
	copy->vector = obj->vector;
	copy->mat = obj->mat;
	copy->mat.refract = obj->mat.refract;
	copy->mat.refract_rate = obj->mat.refract_rate;
	copy_limits2(copy);
}

t_obj				copy_objs(t_obj obj)
{
	t_obj			copy;
	copy.max_dist = obj.max_dist;
	copy.type = obj.type;
	copy.color = obj.color;
	copy.pos = obj.pos;
	copy.limit_active = obj.limit_active;
	copy.limit_nbr = obj.limit_nbr;
	copy.mat.refract_filter = obj.mat.refract_filter;
	copy.mat.sinus = obj.mat.sinus;
	copy.mat.reflex = obj.mat.reflex;
	copy.mat.reflex_filter = obj.mat.reflex_filter;
	copy.mat.damier = obj.mat.damier;
	copy_limits(&obj, &copy);
	copy.neg = obj.neg;
	return (copy);
}

t_scene				copy_scene(t_scene scene)
{
	t_scene			copy;
	int				i;

	i = -1;
	if (!(copy.lights = (t_light *)malloc(scene.nbr_light *
		sizeof(t_light))))
		exit(42);
	while (++i < scene.nbr_light)
		copy.lights[i] = copy_light(scene.lights[i]);
	if (!(copy.obj = (t_obj *)malloc(scene.nbr_obj * sizeof(t_obj))))
		exit(42);
	i = -1;
	while (++i < scene.nbr_obj)
		copy.obj[i] = copy_objs(scene.obj[i]);
	copy.nbr_light = scene.nbr_light;
	copy.nbr_obj = scene.nbr_obj;
	copy.ambient = scene.ambient;
	copy.id = scene.id;
	copy.skybox = scene.skybox;
	copy.cam = scene.cam;
	return (copy);
}

t_rt				*copy_rt(t_rt *e)
{
	t_rt			*copy;

	copy = NULL;
	if ((copy = (t_rt *)malloc(sizeof(t_rt))) == NULL)
		exit(42);
	copy->scene = copy_scene(e->scene);
	copy->mlx.bpp = e->mlx.bpp;
	copy->mlx.size_l = e->mlx.size_l;
	copy->mlx.endian = e->mlx.endian;
	copy->file.larg = e->file.larg;
	copy->file.haut = e->file.haut;
	copy->file.reso = e->file.reso;
	copy->file.reso_buff = e->file.reso_buff;
	copy->file.aliasing = e->file.aliasing;
	return (copy);
}