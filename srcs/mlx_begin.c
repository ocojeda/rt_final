#include "../includes/rt.h"

void			ft_start_rt(t_rt *e)
{
//	e->gtk.started = 1;
	//if (!e->file.haut || !e->file.larg)
	//	exit(0);
	e->mlx.window = mlx_new_window(e->mlx.init, e->file.larg, e->file.haut, "Raytracer");
	e->mlx.image = mlx_new_image(e->mlx.init, e->file.larg, e->file.haut);
    e->mlx.data = mlx_get_data_addr(e->mlx.image, &e->mlx.bpp, 
        &e->mlx.size_l, &e->mlx.endian);
    frame(e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	mlx_mouse_hook(WIN, mousse_hook, e);
    mlx_hook(e->mlx.window, 2, 0, keypress, e);
    mlx_hook(e->mlx.window, 17, 0, mouse_hook_escape, e);
    mlx_loop(e->mlx.init);
	/*mlx_hook(WIN, 3, 0, keyrelease, e);
	mlx_hook(WIN, 17, 0, ft_close, NULL);
	mlx_mouse_hook(WIN, select_obj, e);
	mlx_loop_hook(e->mlx.init, no_event, e);
	mlx_loop(e->mlx.init);*/
}
