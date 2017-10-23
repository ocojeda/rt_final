#include "../includes/rt.h"

int				mousse_hook(int button, int x, int y, void *param)
{
	t_rt	*e;
    t_ray	ray;
    int     temp;

	e = (t_rt *)param;
	if (button == 1)
	{
		ray = ray_init(e, x, y);
        temp = get_min_dist(e, ray);
        if (temp >= 0)
			e->scene.selected_obj = e->scene.id;
		else
            e->scene.selected_obj = -1;    
        e->scene.id = -1;
	}
	return (button);
}