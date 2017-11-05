/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:42:58 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/05 16:34:35 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		keypress3(int keycode, t_rt *e)
{
	if (keycode == KEY_ESC)
		exit(42);
	if (keycode == KEY_ONE)
	{
		e->scene.filters = (e->scene.filters == 1) ? 0 : 1;
		frame(e);
	}
	if (keycode == KEY_TWO)
	{
		e->scene.filters = (e->scene.filters == 2) ? 0 : 2;
		frame(e);
	}
	if (keycode == KEY_THREE)
	{
		e->scene.filters = (e->scene.filters == 3) ? 0 : 3;
		frame(e);
	}
	if (keycode == KEY_FOUR)
	{
		e->scene.filters = (e->scene.filters == 4) ? 0 : 4;
		frame(e);
	}
	if (keycode == KEY_HOME)
		e->scene.selected_obj = -1;
	keypress4(keycode, e, 0);
}

void		keypress2(int keycode, t_rt *e)
{
	if (keycode == KEY_R)
	{
		CCAM.rot.z -= 1;
		frame(e);
	}
	if (keycode == KEY_F)
	{
		CCAM.rot.z += 1;
		frame(e);
	}
	if (keycode == PAGE_UP)
	{
		RES = (RES > 20) ? 20 : RES + 1;
		frame(e);
	}
	if (keycode == PAGE_DOWN)
	{
		RES--;
		if (RES == 0)
			RES = 1;
		frame(e);
	}
	keypress3(keycode, e);
}

void		keypress1(int keycode, t_rt *e)
{
	if (keycode == KEY_Q)
	{
		CCAM.pos.z += 20;
		frame(e);
	}
	if (keycode == KEY_A)
	{
		CCAM.pos.z -= 20;
		frame(e);
	}
	if (keycode == KEY_S)
	{
		CCAM.pos.x -= 15;
		frame(e);
	}
	if (keycode == KEY_W)
	{
		CCAM.pos.x += 15;
		frame(e);
	}
	if (keycode == KEY_DEL)
		screenshot_ppm(e);
	keypress2(keycode, e);
}

int			keypress(int keycode, void *param)
{
	t_rt	*e;

	e = (t_rt *)param;
	if (keycode == KEY_MINUS)
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.z -= 10;
			frame(e);
		}
	if (keycode == KEY_D)
	{
		CCAM.pos.y -= 20;
		frame(e);
	}
	keypress1(keycode, e);
	return (keycode);
}

int			mouse_hook_escape(t_rt *e)
{
	if (e)
		exit(0);
	return (1);
}
