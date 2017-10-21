#include "rtv1.h"

int				calcul_res(t_rt *e, int limit)
{
	int res;
	int air;

	air = e->file.larg * e->file.haut;
    res = 1;
    limit /= 2;
	//if (ALIASING == 2) antialiasing on
    //	limit *= 2;
    //while ((air / res) > limit)
	while ((air / res) > limit)
		res++;
	return (res);
}

void			ft_start_rt(t_rt *e)
{
//	e->gtk.started = 1;
	//if (!e->file.haut || !e->file.larg)
	//	exit(0);
	e->mlx.window = mlx_new_window(e->mlx.init, e->file.larg, e->file.haut, "RTV1");
	e->mlx.image = mlx_new_image(e->mlx.init, e->file.larg, e->file.haut);
    e->mlx.data = mlx_get_data_addr(e->mlx.image, &e->mlx.bpp, 
        &e->mlx.size_l, &e->mlx.endian);
    frame(e);
    mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
    mlx_hook(e->mlx.window, 2, 0, keypress, e);
    mlx_loop(e->mlx.init);
	/*mlx_hook(WIN, 3, 0, keyrelease, e);
	mlx_hook(WIN, 17, 0, ft_close, NULL);
	mlx_mouse_hook(WIN, select_obj, e);
	mlx_loop_hook(e->mlx.init, no_event, e);
	mlx_loop(e->mlx.init);*/
}

void			init_rt(t_rt *e)
{
    e->mlx.init = mlx_init();
    e->file.larg = 800;
    e->file.haut= 800;
    e->file.aliasing = 1;
    e->file.reso = calcul_res(e, 400000);
	e->file.reso_buff = e->file.reso;
    
    e->scene.obj[0].type = SPHERE;
    e->scene.obj[0].color = c_color(180, 190, 200);
    e->scene.obj[0].pos = vec_new3(400, 400, 1000);
	e->scene.obj[0].r = 200;
	e->scene.obj[0].mat.diff = 0.5;

    e->scene.obj[1].type = PLANE;
    e->scene.obj[1].color = c_color(200, 200, 100);
    e->scene.obj[1].pos = vec_new3(400, 400, 900);
	e->scene.obj[1].vector = vec_norme3(vec_new3(0, 0, -1));
	e->scene.obj[1].mat.diff = 1;

    e->scene.obj[2].type = PLANE;
    e->scene.obj[2].color = c_color(0, 200, 0);
    e->scene.obj[2].pos = vec_new3(900, -100, 800);
    e->scene.obj[2].vector = vec_norme3(vec_new3(0, 0.9, 0));
	e->scene.obj[2].mat.diff = 0.5;

    e->scene.obj[3].type = CYLINDER;
    e->scene.obj[3].r = 30;
    e->scene.obj[3].color = c_color(5, 20, 100);
    e->scene.obj[3].pos = vec_new3(500, 400, 300);
	e->scene.obj[3].vector = vec_norme3(vec_new3(0.5, 1, 0));
	e->scene.obj[3].mat.diff = 0.5;

	e->scene.obj[4].type = CONE;
	//k is for angle
    e->scene.obj[4].k = 0.1;
	e->scene.obj[4].color = c_color(100, 15, 100);
	e->scene.obj[4].pos = vec_new3(600, 400, 300);
    e->scene.obj[4].vector = vec_norme3(vec_new3(1, 0.5, 0));
	e->scene.obj[4].mat.diff = 0.5;

    e->scene.nbr_obj = 5;
    e->scene.obj[5].type = END;
	

	e->scene.lights[0].ray.pos = vec_new3(800, 1200, 0);
	e->scene.lights[0].color = c_color(255, 000, 000);
	e->scene.lights[0].intensity = 1;
	e->scene.lights[0].is_init = 0;


	e->scene.lights[1].ray = c_ray(vec_new3(400, 400, -300), vec_new3(0, 0, 0));
	e->scene.lights[1].color = c_color(255, 000, 000);
	e->scene.lights[1].intensity = 0.4;
	e->scene.lights[1].is_init = 0;

	e->scene.ambient = 0.3;
	e->scene.nbr_light = 2;
	//e->scene.lights[1] = END;

	e->scene.cam.pos.x = 400;
	e->scene.cam.pos.y = 400;
    e->scene.cam.pos.z = -2000;

    e->scene.cam.focus_point.x = 401;
	e->scene.cam.focus_point.y = 401;
    e->scene.cam.focus_point.z = 0;
    
	//if (!(e->scene.obj = (t_obj *)malloc(sizeof(t_obj) * MAXOBJ)))
    //   exit(42);
    //if (!(e->scene.lights = (t_light *)malloc(sizeof(t_light) * MAXLIGHT)))
    //    exit(5);
    e->frame = 0;
    /*e->scene.nbr_obj = 0;
	e->scene.nbr_complex = 0;
	e->scene.nbr_light = 0;
	e->scene.nbr_tot = 0;
	e->scene.ambient = 0.1;
	e->scene.skybox.is_init = 0;
	*/
	/*e->scene.selected = -1;
	e->file.path  = NULL;
	e->scene.max_iter = 3;
	key_init(e);*/
}