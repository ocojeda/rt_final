#include "../includes/rt.h"
int				keypress(int keycode, void *param)
{
	t_rt	*e;
	t_ray	dir;
	t_vec3	rx;
	int		i;

	i = 0;
	e = (t_rt *)param;
	dir = ray_init(e, LARGEUR / 2 /RES, HAUTEUR / 2/RES);
	rx = vec_norme3(prod_vec3_matrx4(
		vec_new3(dir.dir.x, 0, dir.dir.z), roty_matrx4(-90)));

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
	if (keycode == PAGE_UP)
	{
		RES += 1;
		if(RES > 20)
			RES = 20;
		frame(e);
	}
	if (keycode == PAGE_DOWN)
	{
		RES--;
		if(RES == 0)
			RES = 1;
		frame(e);
	}
	if (keycode == KEY_HOME)
		e->scene.selected_obj = -1;
	if (keycode == KEY_UP)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.y += 10;
			if(e->scene.obj[e->scene.selected_obj].limit_active)
			{
				while(i < e->scene.obj[e->scene.selected_obj].limit_nbr)
				{
					e->scene.obj[e->scene.selected_obj].limit[i].pos.y += 10;
					i++;
				}
				i = 0;

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
	if (keycode == KEY_DOWN)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.y -= 10;
			if(e->scene.obj[e->scene.selected_obj].limit_active)
			{
				while(i < e->scene.obj[e->scene.selected_obj].limit_nbr)
				{
					e->scene.obj[e->scene.selected_obj].limit[i].pos.y -= 10;
					i++;
				}
				i = 0;
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
	if (keycode == KEY_RIGHT)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.x += 10;
			if(e->scene.obj[e->scene.selected_obj].limit_active)
			{
				while(i < e->scene.obj[e->scene.selected_obj].limit_nbr)
				{
					e->scene.obj[e->scene.selected_obj].limit[i].pos.x += 10;
					i++;
				}
				i = 0;

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
	if (keycode == KEY_LEFT)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.x -= 10;
			if(e->scene.obj[e->scene.selected_obj].limit_active)
			{
				while(i < e->scene.obj[e->scene.selected_obj].limit_nbr)
				{
					e->scene.obj[e->scene.selected_obj].limit[i].pos.x -= 10;
					i++;
				}
				i = 0;

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
	if (keycode == KEY_Q)
	{
		CCAM.rot.z += 1;
		CCAM.rot.z = (CCAM.rot.z > 360) ? 0 : CCAM.rot.z;		
		frame(e);
	}
	if (keycode == KEY_E)
	{
		CCAM.rot.z -= 1;
		CCAM.rot.z = (CCAM.rot.z < 0) ? 360 : CCAM.rot.z;
		frame(e);
	}
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
	if (keycode == KEY_MINUS)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.z -= 10;
			frame(e);
		}
		else
		{
			CCAM.pos.y +=  -20;
			frame(e);
		}
	}
	if (keycode == KEY_W)
	{
		CCAM.pos.z += 20;
		frame(e);
	}
	if (keycode == KEY_S)
	{
		CCAM.pos.z -= 20;
		frame(e);
	}
	if (keycode == KEY_A)
	{
		CCAM.pos.x -= 15;
		frame(e);
	}
	if (keycode == KEY_D)
	{
		CCAM.pos.x += 15;
		frame(e);
	}
	return (keycode);
}
