#include "../includes/rt.h"
int				keypress(int keycode, void *param)
{
	t_rt	*e;
	t_ray	dir;
	t_vec3	rx;

	e = (t_rt *)param;
	dir = ray_init(e, LARGEUR / 2 /RES, HAUTEUR / 2/RES);
	rx = vec_norme3(prod_vec3_matrx4(
		vec_new3(dir.dir.x, 0, dir.dir.z), roty_matrx4(-90)));
	if (keycode == KEY_ESC)
		exit(42);
	if (keycode == PAGE_UP)
	{
		RES += 10;
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
	if (keycode == KEY_X)
	{
		t_mtrx4		transl;
		
			transl = transl_matrx4(CCAM.pos.x, CCAM.pos.y, CCAM.pos.z);
		CCAM.is_circular = (CCAM.is_circular == 1) ? 0 : 1;
		if (CCAM.is_circular == 1)
        CCAM.ctw = transl ;//prod_matrx4(transl, CCAM.ctw);
    	else
			CCAM.ctw = prod_matrx4(CCAM.ctw, transl);
		frame(e);
	}
	if (keycode == KEY_HOME)
		e->scene.selected_obj = -1;
	if (keycode == KEY_UP)
	{
		if (e->scene.selected_obj >= 0)
		{
			e->scene.obj[e->scene.selected_obj].pos.y += 10;
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
			CCAM.pos.y += (dir.dir.y < 0) ? dir.dir.y * -(20 / dir.dir.y) : dir.dir.y * (20 / dir.dir.y);
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
			CCAM.pos.y += (dir.dir.y < 0) ? dir.dir.y * (20 / dir.dir.y) : dir.dir.y * -(20 / dir.dir.y);
			frame(e);
		}
	}
	if (keycode == KEY_W)
	{
		CCAM.pos.z += (dir.dir.z < 0) ? dir.dir.z * -(20 / dir.dir.z) : dir.dir.z * (20 / dir.dir.z);
		frame(e);
	}
	if (keycode == KEY_S)
	{
		CCAM.pos.z += (dir.dir.z < 0) ? dir.dir.z * (20 / dir.dir.z) : dir.dir.z * -(20 / dir.dir.z);
		frame(e);
	}
	if (keycode == KEY_A)
	{
		CCAM.pos.x -= dir.dir.x * (15 / dir.dir.x);
		frame(e);
	}
	if (keycode == KEY_D)
	{
		CCAM.pos.x += dir.dir.x * (15 / dir.dir.x);
		frame(e);
	}

	// e->keys.key_w = (keycode == KEY_W) ? 1 : e->keys.key_w;
	// e->keys.key_a = (keycode == KEY_A) ? 1 : e->keys.key_a;
	// e->keys.key_s = (keycode == KEY_S) ? 1 : e->keys.key_s;
	// e->keys.key_d = (keycode == KEY_D) ? 1 : e->keys.key_d;
	// e->keys.key_q = (keycode == KEY_Q) ? 1 : e->keys.key_q;
	// e->keys.key_e = (keycode == KEY_E) ? 1 : e->keys.key_e;
	// e->keys.key_up = (keycode == KEY_UP) ? 1 : e->keys.key_up;
	// e->keys.key_left = (keycode == KEY_LEFT) ? 1 : e->keys.key_left;
	// e->keys.key_down = (keycode == KEY_DOWN) ? 1 : e->keys.key_down;
	// e->keys.key_right = (keycode == KEY_RIGHT) ? 1 : e->keys.key_right;
	// e->keys.key_plus = (keycode == KEY_PLUS ||
	// keycode == 24) ? 1 : e->keys.key_plus;
	// e->keys.key_minus = (keycode == KEY_MINUS ||
	// keycode == 27) ? 1 : e->keys.key_minus;
	// e->keys.key_n = (keycode == KEY_N) ? 1 : e->keys.key_n;
	// e->keys.key_o = (keycode == KEY_O) ? 1 : e->keys.key_o;
	//onepress(keycode, e);
	// auto_res(keycode, e);
    // key(e);
    //mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	return (keycode);
}
