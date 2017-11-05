/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_begin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:16:33 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/05 15:47:16 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			ft_start_rt(t_rt *e)
{
	e->mlx.window = mlx_new_window(e->mlx.init, e->file.larg,
			e->file.haut, "Raytracer");
	e->mlx.image = mlx_new_image(e->mlx.init, e->file.larg, e->file.haut);
	e->mlx.data = mlx_get_data_addr(e->mlx.image, &e->mlx.bpp,
			&e->mlx.size_l, &e->mlx.endian);
	frame(e);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	mlx_mouse_hook(WIN, mousse_hook, e);
	mlx_hook(e->mlx.window, 2, 0, keypress, e);
	mlx_hook(e->mlx.window, 17, 0, mouse_hook_escape, e);
	mlx_loop(e->mlx.init);
}
