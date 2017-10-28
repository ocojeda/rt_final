#include "../includes/rt.h"

int				parse_texture(t_rt *e)
{
	if ((e->scene.skybox.ptr = mlx_xpm_file_to_image(INIT,
		"xpm_images/dora.xpm", &e->scene.skybox.width,
		&e->scene.skybox.height)))
	//if ((e->scene.skybox.ptr = mlx_xpm_file_to_image(INIT,
	//	"xpm_images/tgros.xpm", &e->scene.skybox.width,
	//	&e->scene.skybox.height)))
	//if ((e->scene.skybox.ptr = mlx_xpm_file_to_image(INIT,
	//	"xpm_images/myernaux.xpm", &e->scene.skybox.width,
	//	&e->scene.skybox.height)))
	{
		if (!(e->scene.skybox.data = mlx_get_data_addr(e->scene.skybox.ptr,
			&e->scene.skybox.bpp, &e->scene.skybox.sizl,
			&e->scene.skybox.endian)))
			ft_putstr("skybox can't be loaded");
		else
			e->scene.skybox.is_init = 1;
	}
	else
		ft_putstr("skybox can't be loaded");
	return 1;
}

void			ft_start_rt(t_rt *e)
{
//	e->gtk.started = 1;
	//if (!e->file.haut || !e->file.larg)
	//	exit(0);
	e->mlx.window = mlx_new_window(e->mlx.init, e->file.larg, e->file.haut, "Raytracer");
	e->mlx.image = mlx_new_image(e->mlx.init, e->file.larg, e->file.haut);
    e->mlx.data = mlx_get_data_addr(e->mlx.image, &e->mlx.bpp, 
		&e->mlx.size_l, &e->mlx.endian);
	parse_texture(e);
    frame(e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	mlx_mouse_hook(WIN, mousse_hook, e);
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

	if (!(e->scene.obj = (t_obj *)malloc(sizeof(t_obj) * MAXOBJ)))
		exit(42);

	/*e->scene.obj[0].type = PLANE;
	e->scene.obj[0].color = c_color(70,30,255);
	e->scene.obj[0].pos = vec_new3(4000, 0, 0);
	e->scene.obj[0].vector = vec_norme3(vec_new3(-1, 0, 0));
	e->scene.obj[0].mat.diff = 0.4;
	e->scene.obj[0].mat.reflex = 0;
	e->scene.obj[0].mat.refract = 0;
	e->scene.obj[0].neg = 0;
	e->scene.obj[0].limit_active = 0;*/

	/*e->scene.obj[7].type = PLANE;
	e->scene.obj[7].color = c_color(70,30,255);
	e->scene.obj[7].pos = vec_new3(-3000, 0, 0);
	e->scene.obj[7].vector = vec_norme3(vec_new3(-1, 0, 0));
	e->scene.obj[7].mat.diff = 0.4;
	e->scene.obj[7].mat.reflex = 0;
	e->scene.obj[7].mat.refract = 0;
	e->scene.obj[7].neg = 0;
	e->scene.obj[7].limit_active = 0;*/

    /*e->scene.obj[1].type = SPHERE;
    e->scene.obj[1].color = c_color(55,150,200);
    e->scene.obj[1].pos = vec_new3(0, 0, 4000);
	e->scene.obj[1].vector = vec_norme3(vec_new3(0, 0, -1));
	e->scene.obj[1].r = 500;
	e->scene.obj[1].mat.reflex = 0;
	e->scene.obj[1].limit_active = 1;
	e->scene.obj[1].limit_nbr = 1;
	e->scene.obj[1].mat.diff = 0.4;
	e->scene.obj[1].mat.refract = 0;
	e->scene.obj[1].neg = 0;

	e->scene.obj[1].limit[0].type = PLANE;
	e->scene.obj[1].limit[0].pos = vec_new3(0, 0, 4000);
	e->scene.obj[1].limit[0].vector = vec_norme3(vec_new3(1, 0, 0));*/

	// ICI FAIRE LES LIMITE DE LA SPHERE AU DESSUS
	
	/*e->scene.obj[8].type = PLANE;
    e->scene.obj[8].color = c_color(70,30,100);
    e->scene.obj[8].pos = vec_new3(0, 0, -8000);
	e->scene.obj[8].vector = vec_norme3(vec_new3(0, 0, 1));
	e->scene.obj[8].mat.diff = 0.4;
	e->scene.obj[8].mat.reflex = 0;
	e->scene.obj[8].mat.refract = 0;
	e->scene.obj[8].neg = 0;
	e->scene.obj[8].limit_active = 0;*/

	/*e->scene.obj[2].type = PLANE;
    e->scene.obj[2].color = c_color(70,30,100);
    e->scene.obj[2].pos = vec_new3(0, -4000, 0);
    e->scene.obj[2].vector = vec_norme3(vec_new3(0, 1, 0));
	e->scene.obj[2].mat.diff = 0.4;
	e->scene.obj[2].mat.reflex = 0;
	e->scene.obj[2].mat.refract = 0;
	e->scene.obj[2].neg = 0;
	e->scene.obj[2].limit_active = 0;*/

	/*e->scene.obj[9].type = PLANE;
    e->scene.obj[9].color = c_color(70,30,100);
    e->scene.obj[9].pos = vec_new3(0, 4000, 0);
    e->scene.obj[9].vector = vec_norme3(vec_new3(0, -1, 0));
	e->scene.obj[9].mat.diff = 0.4;
	e->scene.obj[9].mat.reflex = 0;
	e->scene.obj[9].mat.refract = 0;
	e->scene.obj[9].neg = 0;
	e->scene.obj[9].limit_active = 0;*/

	/*e->scene.obj[3].type = CYLINDER;
	e->scene.obj[3].r = 200;
 	e->scene.obj[3].color = c_color(0, 255, 255);
    e->scene.obj[3].pos = vec_new3(200, 100, 300);
	e->scene.obj[3].vector = vec_norme3(vec_new3(0.5, 1, 0));
	e->scene.obj[3].mat.diff = 0.2;
	e->scene.obj[3].mat.reflex = 0;
	e->scene.obj[3].mat.refract = 0;
	e->scene.obj[3].neg = 0;
	e->scene.obj[3].limit_active = 1;
	e->scene.obj[3].limit_nbr = 1;
	e->scene.obj[3].limit[0].type = PLANE;
	e->scene.obj[3].limit[0].pos = vec_new3(200, 100, 300);
	e->scene.obj[3].limit[0].vector = vec_norme3(vec_new3(-0.5, 1, 0));*/

	// AU DESSUS LES LIMITES
	
	e->scene.obj[4].type = PARABOLOID;
    e->scene.obj[4].k = 50;
	e->scene.obj[4].color = c_color(255, 15, 10);
	e->scene.obj[4].pos = vec_new3(60, 900, 3000);
    e->scene.obj[4].vector = vec_norme3(vec_new3(1, 0.5, 0));
	e->scene.obj[4].mat.diff = 0.4;
	e->scene.obj[4].mat.reflex = 0;
	e->scene.obj[4].mat.refract = 0;
	e->scene.obj[4].neg = 0;
	e->scene.obj[4].limit_active = 1;
	e->scene.obj[4].limit_nbr = 1;
	e->scene.obj[4].limit[0].type = PLANE;
	e->scene.obj[4].limit[0].pos = vec_new3(60, 1000, 3000);
	e->scene.obj[4].limit[0].vector = vec_norme3(vec_new3(0.2, 1, 0));

	/*e->scene.obj[5].type = CONE;
	e->scene.obj[5].color = c_color(250, 100, 100);
	e->scene.obj[5].pos = vec_new3(-300, 200, 1000);
	e->scene.obj[5].vector = vec_norme3(vec_new3(-1, 0, 0));
	e->scene.obj[5].mat.diff = 1;
	e->scene.obj[5].mat.reflex = 0;
	e->scene.obj[5].mat.refract = 0;
	e->scene.obj[5].neg = 0;
	e->scene.obj[5].k = 0.3;
	e->scene.obj[5].limit_active = 1;
	e->scene.obj[5].limit_nbr = 2;
	e->scene.obj[5].limit[0].type = PLANE;
	e->scene.obj[5].limit[0].pos = vec_new3(-300, 200, 1000);
	e->scene.obj[5].limit[0].vector = vec_norme3(vec_new3(1, 0, 0));
	e->scene.obj[5].limit[1].type = PLANE;
	e->scene.obj[5].limit[1].pos = vec_new3(-900, 200, 1000);
	e->scene.obj[5].limit[1].vector = vec_norme3(vec_new3(-1, 0, 0));*/

	// AU DESSUS LES LIMITES

	/*e->scene.obj[6].type = PLANE;
    e->scene.obj[6].color = c_color(150, 150, 0);
	e->scene.obj[6].pos = vec_new3(250, 0, 500);
	e->scene.obj[6].vector = vec_norme3(vec_new3(0, 0, 1));
	e->scene.obj[6].mat.reflex = 0;
	e->scene.obj[6].mat.refract = 0;
	e->scene.obj[6].mat.diff = 0;
	e->scene.obj[6].neg = 0;
	e->scene.obj[6].limit_active = 1;
	e->scene.obj[6].limit_nbr = 3;
	e->scene.obj[6].limit[0].type = PLANE;
	e->scene.obj[6].limit[0].pos = vec_new3(250, -200, 500);
	e->scene.obj[6].limit[0].vector = vec_norme3(vec_new3(0, -1, 0));
	e->scene.obj[6].limit[1].type = PLANE;
	e->scene.obj[6].limit[1].pos = vec_new3(850, 0, 500);
	e->scene.obj[6].limit[1].vector = vec_norme3(vec_new3(0.5, 0.5, 0));
	e->scene.obj[6].limit[2].type = PLANE;
	e->scene.obj[6].limit[2].pos = vec_new3(400, 0, 500);
	e->scene.obj[6].limit[2].vector = vec_norme3(vec_new3(-0.5, 0.5, 0));*/

	e->scene.nbr_obj = 10;
    e->scene.obj[10].type = END;

	//if (!(e->scene.obj = (t_obj *)malloc(sizeof(t_obj) * MAXOBJ)))
    //   exit(42);
    //if (!(e->scene.lights = (t_light *)malloc(sizeof(t_light) * MAXLIGHT)))
    //    exit(5);
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
