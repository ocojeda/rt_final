/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:57:59 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 20:03:10 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			screenshot_ppm(t_rt *e)
{
	t_file		export;
	int			pos;
	static int	nb = 0;
	char		*nbr;
	char		*name;

	ft_putendl("Exporting image...");
	nbr = ft_itoa(nb++);
	name = ft_strjoin(nbr, "screenshot.ppm");
	if (!(export.fd_exp = open(name, O_WRONLY | O_CREAT, 00755)))
		return ;
	export.haut = -1;
	while (++export.haut < HAUTEUR && (export.larg = -1) == -1)
		while (++export.larg < LARGEUR)
		{
			pos = (export.larg * e->mlx.bpp / 8 + export.haut * e->mlx.size_l);
			write(export.fd_exp, &DATA[pos + 2], 1);
			write(export.fd_exp, &DATA[pos + 1], 1);
			write(export.fd_exp, &DATA[pos], 1);
		}
	free(nbr);
	free(name);
	close(export.fd_exp);
	ft_putendl("Image exported !");
}
