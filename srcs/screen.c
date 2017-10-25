#include "../includes/rt.h"

/*void			screenshot_xpm(t_rt *e)
{
	t_file		export;
	int			pos;
	static int	nb = 0;
	char		*nbr;
	char		*name;

	ft_putendl("Exporting image in xpm...");
	nbr = ft_itoa(nb++);
	name = ft_strjoin( nbr ,"screenshot.xpm");
	if (!(export.fd_exp = open(name, O_WRONLY | O_CREAT, 00755)))
		return ;
	ft_putstr_fd("P6 ", export.fd_exp);
	ft_putnbr_fd(LARGEUR, export.fd_exp);
	ft_putstr_fd(" ", export.fd_exp);
	ft_putnbr_fd(HAUTEUR, export.fd_exp);
	ft_putstr_fd(" 255\n", export.fd_exp);
	export.haut = -1;
	while (++export.haut < HAUTEUR)
	{
		export.larg = -1;
		while (++export.larg < LARGEUR)
		{
			pos = (export.larg * e->mlx.bpp / 8 + export.haut * e->mlx.size_l);
			write(export.fd_exp, &DATA[pos + 2], 1);
			write(export.fd_exp, &DATA[pos + 1], 1);
			write(export.fd_exp, &DATA[pos], 1);
		}
	}
	close(export.fd_exp);
	ft_putendl("Image exported !");
}*/

void			screenshot_ppm(t_rt *e)
{
	t_file		export;
	int			pos;
	static int	nb = 0;
	char		*nbr;
	char		*name;

	ft_putendl("Exporting image in ppm...");
	nbr = ft_itoa(nb++);
	name = ft_strjoin( nbr ,"screenshot.ppm");
	if (!(export.fd_exp = open(name, O_WRONLY | O_CREAT, 00755)))
		return ;
	ft_putstr_fd("P6 ", export.fd_exp);
	ft_putnbr_fd(LARGEUR, export.fd_exp);
	ft_putstr_fd(" ", export.fd_exp);
	ft_putnbr_fd(HAUTEUR, export.fd_exp);
	ft_putstr_fd(" 255\n", export.fd_exp);
	export.haut = -1;
	while (++export.haut < HAUTEUR)
	{
		export.larg = -1;
		while (++export.larg < LARGEUR)
		{
			pos = (export.larg * e->mlx.bpp / 8 + export.haut * e->mlx.size_l);
			write(export.fd_exp, &DATA[pos + 2], 1);
			write(export.fd_exp, &DATA[pos + 1], 1);
			write(export.fd_exp, &DATA[pos], 1);
		}
	}
	close(export.fd_exp);
	ft_putendl("Image exported !");
}