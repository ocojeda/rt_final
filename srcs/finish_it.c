#include "../includes/rt.h"

void				finish_it(t_rt **th_e, t_rt *e)
{
	int i;

	i = 0;
	while (i < NB_THREADS)
	{
		free(th_e[i]->thread.colors);
		free(th_e[i]->scene.lights);
		free(th_e[i]->scene.obj);
		free(th_e[i]);
		i++;
	}
	filters(e);
	free(th_e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
}