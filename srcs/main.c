#include "../includes/rt.h"

int main (int argc, char **argv)
{
	t_rt	*e;
    
    if (!(e = (t_rt *)malloc(sizeof(t_rt))))
        return (0);
    init_rt(e);
    if (argc == 2)
    {
    	ft_gtk_start_launcher(e);
    }
    else
    	ft_start_rt(e);
    
    (void)argv;
    (void)argc;
 
    return 0;
}
