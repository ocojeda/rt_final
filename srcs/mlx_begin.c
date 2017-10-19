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
    e->scene.obj[0].color = c_color(0, 0, 200);
    e->scene.obj[0].pos = vec_new3(400, 400, 500);
    e->scene.obj[0].r = 200;

    e->scene.obj[1].type = PLANE;
    e->scene.obj[1].color = c_color(200, 200, 0);
    e->scene.obj[1].pos = vec_new3(400, 0, 800);
    e->scene.obj[1].vector = vec_new3(0, 1, 0);

    e->scene.obj[2].type = PLANE;
    e->scene.obj[2].color = c_color(0, 200, 0);
    e->scene.obj[2].pos = vec_new3(300, 0, 800);
    e->scene.obj[2].vector = vec_new3(1, 0, 0);

    e->scene.obj[3].type = CYLINDER;
    e->scene.obj[3].r = 4;
    e->scene.obj[3].color = c_color(15, 50, 150);
    e->scene.obj[3].pos = vec_new3(300, 400, 0);
	e->scene.obj[3].vector = vec_new3(0, 1, 0);
	
	e->scene.obj[4].type = CONE;
	//k is for angle
    e->scene.obj[4].k = 0.1;
	e->scene.obj[4].color = c_color(100, 15, 200);
	e->scene.obj[4].pos = vec_new3(600, 400, 0);
    e->scene.obj[4].vector = vec_new3(1, 0.1, 0);
    
    e->scene.nbr_obj = 5;
    e->scene.obj[5].type = END;
    
	e->scene.cam.pos.x = 400;
	e->scene.cam.pos.y = 400;
	e->scene.cam.pos.z = -1000;
	e->scene.cam.fov = 45;


	
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