#include "../includes/rt.h"

int main (int argc, char **argv)
{
	t_rt	*e;
    
    if (!(e = (t_rt *)malloc(sizeof(t_rt))))
        return (0);
    init_rt(e);
    parse(e, argc, argv);
    ft_start_rt(e);
    return 0;
}
