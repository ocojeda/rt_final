#include "rtv1.h"

int				keypress(int keycode, void *param)
{
	t_rt	*e;

	e = (t_rt *)param;
	if (keycode == KEY_ESC)
		exit(42);
	if (keycode == PAGE_UP)
	{
		RES++;
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
	if (keycode == KEY_UP)
	{
		e->scene.cam.focus_point.y += 10;
		frame(e);
	}
	if (keycode == KEY_DOWN)
	{
		e->scene.cam.focus_point.y -= 10;
		frame(e);
	}
	if (keycode == KEY_RIGHT)
	{
		e->scene.cam.focus_point.x += 10;
		frame(e);
	}
	if (keycode == KEY_LEFT)
	{
		e->scene.cam.focus_point.x -= 10;
		frame(e);
	}
	if (keycode == KEY_PLUS)
	{
		e->scene.cam.focus_point.z += 10;
		frame(e);
	}
	if (keycode == KEY_MINUS)
	{
		e->scene.cam.focus_point.z -= 10;
		frame(e);
	}
	
	if (keycode == KEY_W)
	{
		e->scene.cam.pos.z += 10;
		frame(e);
	}if (keycode == KEY_S)
	{
		e->scene.cam.pos.z -= 10;
		frame(e);
	}if (keycode == KEY_A)
	{
		e->scene.cam.pos.x += 10;
		frame(e);
	}if (keycode == KEY_D)
	{
		e->scene.cam.pos.x -= 10;
		frame(e);
	}
	/*e->keys.key_w = (keycode == KEY_W) ? 1 : e->keys.key_w;
	e->keys.key_a = (keycode == KEY_A) ? 1 : e->keys.key_a;
	e->keys.key_s = (keycode == KEY_S) ? 1 : e->keys.key_s;
	e->keys.key_d = (keycode == KEY_D) ? 1 : e->keys.key_d;
	e->keys.key_q = (keycode == KEY_Q) ? 1 : e->keys.key_q;
	e->keys.key_e = (keycode == KEY_E) ? 1 : e->keys.key_e;
	e->keys.key_up = (keycode == KEY_UP) ? 1 : e->keys.key_up;
	e->keys.key_left = (keycode == KEY_LEFT) ? 1 : e->keys.key_left;
	e->keys.key_down = (keycode == KEY_DOWN) ? 1 : e->keys.key_down;
	e->keys.key_right = (keycode == KEY_RIGHT) ? 1 : e->keys.key_right;
	e->keys.key_plus = (keycode == KEY_PLUS ||
	keycode == 24) ? 1 : e->keys.key_plus;
	e->keys.key_minus = (keycode == KEY_MINUS ||
	keycode == 27) ? 1 : e->keys.key_minus;
	e->keys.key_n = (keycode == KEY_N) ? 1 : e->keys.key_n;
	e->keys.key_o = (keycode == KEY_O) ? 1 : e->keys.key_o;
	onepress(keycode, e);
	auto_res(keycode, e);
    key(e);*/
    //mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	return (keycode);
}