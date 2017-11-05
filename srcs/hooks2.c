/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 00:03:28 by ocojeda-          #+#    #+#             */
/*   Updated: 2017/11/05 16:20:54 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		keypress8(int keycode, t_rt *e)
{
	if (keycode == KEY_PLUS)
	{
		if (e->scene.selected_obj >= 0)
			e->scene.obj[e->scene.selected_obj].pos.z += 10;
		frame(e);
	}
	if (keycode == KEY_E)
	{
		CCAM.pos.y += 20;
		frame(e);
	}
}

void		keypress7(int keycode, t_rt *e, int i)
{
	if (keycode == KEY_LEFT)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.x -= 10;
			if (e->scene.obj[e->scene.selected_obj].limit_active)
			{
				while (i < e->scene.obj[e->scene.selected_obj].limit_nbr)
				{
					e->scene.obj[e->scene.selected_obj].limit[i].pos.x -= 10;
					i++;
				}
			}
			frame(e);
		}
		else
		{
			CCAM.rot.y -= 1;
			frame(e);
		}
	}
	keypress8(keycode, e);
}

void		keypress6(int keycode, t_rt *e, int i)
{
	if (keycode == KEY_RIGHT)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.x += 10;
			if (e->scene.obj[e->scene.selected_obj].limit_active)
			{
				while (i < e->scene.obj[e->scene.selected_obj].limit_nbr)
				{
					e->scene.obj[e->scene.selected_obj].limit[i].pos.x += 10;
					i++;
				}
			}
			frame(e);
		}
		else
		{
			CCAM.rot.y += 1;
			frame(e);
		}
	}
	keypress7(keycode, e, 0);
}

void		keypress5(int keycode, t_rt *e, int i)
{
	if (keycode == KEY_DOWN)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.y -= 10;
			if (e->scene.obj[e->scene.selected_obj].limit_active)
			{
				while (i < e->scene.obj[e->scene.selected_obj].limit_nbr)
				{
					e->scene.obj[e->scene.selected_obj].limit[i].pos.y -= 10;
					i++;
				}
			}
			frame(e);
		}
		else
		{
			CCAM.rot.x -= 1;
			frame(e);
		}
	}
	keypress6(keycode, e, 0);
}

void		keypress4(int keycode, t_rt *e, int i)
{
	if (keycode == KEY_UP)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.y += 10;
			if (e->scene.obj[e->scene.selected_obj].limit_active)
			{
				while (i < e->scene.obj[e->scene.selected_obj].limit_nbr)
				{
					e->scene.obj[e->scene.selected_obj].limit[i].pos.y += 10;
					i++;
				}
			}
			frame(e);
		}
		else
		{
			CCAM.rot.x += 1;
			frame(e);
		}
	}
	keypress5(keycode, e, 0);
}
