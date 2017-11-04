/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:17:56 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 20:18:47 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		main(int argc, char **argv)
{
	t_rt	*e;

	if (!(e = (t_rt *)malloc(sizeof(t_rt))))
		return (0);
	e->mlx.init = mlx_init();
	e->scene.nbr_light = 0;
	e->scene.nbr_obj = 0;
	e->frame = 0;
	if (argc >= 2)
	{
		parse(e, argc, argv);
		ft_start_rt(e);
	}
	else
		ft_gtk_start_launcher(e);
	return (0);
}
