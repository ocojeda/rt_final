/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 21:01:41 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:10:01 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		keypress8(int keycode, t_rt *e)
{
	if (keycode == KEY_PLUS)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.z += 10;
			frame(e);
		}
		else
		{
			CCAM.pos.y += 20;
			frame(e);
		}
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
			CCAM.rot.y = (CCAM.rot.y < 0) ? 360 : CCAM.rot.y;
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
			CCAM.rot.y = (CCAM.rot.y > 360) ? 0 : CCAM.rot.y;
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
			CCAM.rot.x = (CCAM.rot.x < 0) ? 360 : CCAM.rot.x;
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
			CCAM.rot.x = (CCAM.rot.x > 360) ? 0 : CCAM.rot.x;
			frame(e);
		}
	}
	keypress5(keycode, e, 0);
}
