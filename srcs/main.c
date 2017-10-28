#include "../includes/rt.h"

int     main(int argc, char **argv)
{
	t_rt	*e;

    if (!(e = (t_rt *)malloc(sizeof(t_rt))))
        return (0);
    e->mlx.init = mlx_init();
    e->scene.nbr_light = 0;
    e->scene.nbr_obj = 0;
    e->frame = 0;
    parse(e, argc, argv);
    ft_start_rt(e);
    return 0;
}
