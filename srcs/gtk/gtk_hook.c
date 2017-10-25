#include "../includes/rt.h"

void			new_rt(void)
{
	t_rt	*e;

	if (!(e = (t_rt *)malloc(sizeof(t_rt))))
		exit(42);
	init_rt(e);
	ft_gtk_start_launcher(e);
}

void			show_settings(t_rt *e)
{
	mlx_destroy_window(INIT, WIN);
	ft_gtk_start_settings(e);
}

void			gtk_hook(int keycode, t_rt *e)
{
	(void)e;
	//if (keycode == KEY_G || keycode == KEY_H)
		//key_init(e);
	if (keycode == KEY_G)
		new_rt();
	//else if (keycode == KEY_H)
		//show_settings(e);
}