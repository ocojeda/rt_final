#include "rtv1.h"

unsigned int	ret_colors(t_color colo)
{
	unsigned int	total;
	unsigned int	temp;

	total = 0;
	if (colo.r > 0)
	{
		temp = (int)colo.r * 256 * 256;
		total += temp;
	}
	if (colo.g > 0)
	{
		temp = (int)colo.g * 256;
		total += temp;
	}
	if (colo.b > 0)
	{
		temp = (int)colo.b;
		total += temp;
	}
	return (total);
}

t_color			c_color(float r, float g, float b)
{
	t_color		color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color			raytrace(int x, int y, t_rt *e)
{
	t_color		color;
//	t_ray		ray;

//	ray = ray_init(e, x * RES / ALIASING, y * RES / ALIASING);
//	color = get_pxl_color(e, ray);
    (void)e;
    color = c_color(x,y,99); 
	return (color);
}

void			*drawline(void *arg)
{
	t_rt		*e;
	int			y;
	int			x;
	int			i;

	e = (t_rt *)arg;
	if (!(e->thread.colors =
	malloc((e->thread.h * e->thread.w + 1) * sizeof(t_color))))
		exit(42);
	y = e->thread.y;
	i = 0;
	while (y < e->thread.max_y)
	{
		x = 0;
		while (x < e->thread.w)
		{
			e->thread.colors[i] = raytrace(x, y, e);
//			if (e->scene.filters == 5)
//				e->thread.colors[i] = fl_cartoon(e->thread.colors[i]);
			++x;
			++i;
		}
		++y;
	}
	return (NULL);
}

t_scene				copy_scene(t_scene scene)
{
	t_scene			copy;
	int				i;

    i = -1;
    copy = scene;
//	if (!(copy.lights = (t_light *)malloc(scene.nbr_light *
//	sizeof(t_light))))
//		exit(42);
//	while (++i < scene.nbr_light)
//		copy.lights[i] = copy_light(scene.lights[i]);
//	if (!(copy.obj = (t_obj *)malloc(scene.nbr_obj * sizeof(t_obj))))
//		exit(42);
//	i = -1;
//	while (++i < scene.nbr_obj)
//		copy.obj[i] = copy_objs(scene.obj[i]);
/*	copy.skybox = scene.skybox;
	copy.last = scene.last;
	copy.nbr_light = scene.nbr_light;
	copy.nbr_obj = scene.nbr_obj;
	copy.nbr_tot = scene.nbr_tot;
	copy.ambient = scene.ambient;
	copy.id = scene.id;
	copy.supersampling = scene.supersampling;
	copy.cam = scene.cam;
	copy.filters = scene.filters;
*/	return (copy);
}


t_rt				*copy_rt(t_rt *e)
{
	t_rt			*copy;

	copy = NULL;
	if ((copy = (t_rt *)malloc(sizeof(t_rt))) == NULL)
		exit(42);
	copy->scene = copy_scene(e->scene);
	copy->file.larg = e->file.larg;
	copy->file.haut = e->file.haut;
	copy->file.reso = e->file.reso;
	copy->file.aliasing = e->file.aliasing;
	return (copy);
}

t_rt			**launch_thread(t_rt *e)
{
	int			i;
	pthread_t	th[NB_THREADS];
	t_rt		**th_e;

	if (!(th_e = (t_rt **)malloc(NB_THREADS * sizeof(t_rt *))))
		return (NULL);
	i = -1;
	while (++i < NB_THREADS)
	{
		th_e[i] = copy_rt(e);
		THREAD.h = HAUTEUR * e->file.aliasing;
		THREAD.w = LARGEUR * e->file.aliasing;
		THREAD.h /= RES;
		THREAD.w /= RES;
		THREAD.y = ((THREAD.h) / NB_THREADS) * i;
		THREAD.max_y = THREAD.y + ((THREAD.h) / NB_THREADS);
		//if (e->file.aliasing == 1)
			pthread_create(&th[i], NULL, drawline, (void *)th_e[i]);
		//else
		//	pthread_create(&th[i], NULL, drawlinex2, (void *)th_e[i]);
	}
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(th[i], NULL);
	return (th_e);
}

void			mlx_pixel(int x, int y, t_rt *e, int color)
{
	int		pos;

	if (x < LARGEUR && y < HAUTEUR)
	{
		pos = x * 4 + y * e->mlx.size_l;
		e->mlx.data[pos] = color;
		e->mlx.data[pos + 1] = color >> 8;
		e->mlx.data[pos + 2] = color >> 16;
	}
}

void			pixel_to_image(int x, int y, t_rt *e, int color)
{
	int max_x;
	int max_y;
	int start_y;

	x = x * RES;
	y = y * RES;
	start_y = y;
	max_x = x + RES;
	max_y = y + RES;
	while (x <= max_x)
	{
		while (y <= max_y)
		{
			if ((x >= 0 && y >= 0) || (x < RES_W && y < RES_H))
				mlx_pixel(x, y, e, color);
			y++;
		}
		y = start_y;
		x++;
	}
}

void			frame(t_rt *e)
{
    (void)e;
	t_rt		**th_e;
	int			i;
	int			i2;
    int         ny;
    int         nx;

    e->frame++;
    th_e = NULL;
//	matrix_init(e);
    th_e = launch_thread(e);
	i = -1;
	while (++i < NB_THREADS)
	{
		ny = (th_e[i]->thread.y / e->file.aliasing) - 1;
		i2 = -1;
		while (++ny < th_e[i]->thread.max_y / e->file.aliasing)
		{
			nx = -1;
			while (++nx < th_e[i]->thread.w / e->file.aliasing)
                pixel_to_image(nx, ny, e, 
                    ret_colors(th_e[i]->thread.colors[++i2]));
		}
//		dname(e, th_e, i);
	}
//	filters(e);
//	free(th_e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	//disp_cam(e, 0x00FFFFFF);
}