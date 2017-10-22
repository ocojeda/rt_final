#include "rtv1.h"

int				keypress(int keycode, void *param)
{
	t_rt	*e;
	t_ray	dir;
	t_vec3	rx;

	e = (t_rt *)param;
	dir = ray_init(e, LARGEUR / 2, HAUTEUR / 2);
	rx = vec_norme3(prod_vec3_matrx4(
		vec_new3(dir.dir.x, 0, dir.dir.z), roty_matrx4(-90)));
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
		CCAM.rot.x += 1;
		CCAM.rot.x = (CCAM.rot.x > 360) ? 0 : CCAM.rot.x;
		frame(e);
	}
	if (keycode == KEY_DOWN)
	{
		CCAM.rot.x -= 1;
		CCAM.rot.x = (CCAM.rot.x < 0) ? 360 : CCAM.rot.x;
		frame(e);
	}
	if (keycode == KEY_RIGHT)
	{
		CCAM.rot.y += 1;
		CCAM.rot.y = (CCAM.rot.y > 360) ? 0 : CCAM.rot.y;
		frame(e);
	}
	if (keycode == KEY_LEFT)
	{
		CCAM.rot.y -= 1;
		CCAM.rot.y = (CCAM.rot.y < 0) ? 360 : CCAM.rot.y;
		frame(e);
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
		CCAM.pos.y += dir.dir.y * 20;
		frame(e);
	}
	if (keycode == KEY_MINUS)
	{
		CCAM.pos.y -= dir.dir.y * 20;
		frame(e);
	}
	
	if (keycode == KEY_W)
	{
		if (dir.dir.z < 0)
		CCAM.pos.z -= dir.dir.z * 20;
		else
		CCAM.pos.z += dir.dir.z * 20;
		frame(e);
	}
	if (keycode == KEY_S)
	{
		if (dir.dir.z < 0)
		CCAM.pos.z += dir.dir.z * 20;
		else
		CCAM.pos.z -= dir.dir.z * 20;
		frame(e);
	}if (keycode == KEY_A)
	{
		if (rx.x < 0)
		CCAM.pos.x += rx.x * 20;
		else
		CCAM.pos.x -= rx.x * 20;
		frame(e);
	}if (keycode == KEY_D)
	{
		if (rx.x < 0)
		CCAM.pos.x -= rx.x * 20;
		else
		CCAM.pos.x += rx.x * 20;
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
/*
void			move(t_rt *e, t_vec3 *vec, int speed)
{
	t_ray	dir;
	t_vec3	rx;

	dir = ray_init(e, LARGEUR / 2, HAUTEUR / 2);
	rx = vec_norme3(prod_vec3_matrx4(
		vec_new3(dir.dir.x, 0, dir.dir.z), roty_matrx4(-90)));
	if ((e->keys.key_w && !e->keys.key_s) || (e->keys.key_s && !e->keys.key_w))
	{
		vec->x += (e->keys.key_w) ? dir.dir.x * speed : dir.dir.x * -speed;
		vec->y += (e->keys.key_w) ? dir.dir.y * speed : dir.dir.y * -speed;
		vec->z += (e->keys.key_w) ? dir.dir.z * speed : dir.dir.z * -speed;
	}
	if ((e->keys.key_a && !e->keys.key_d) || (e->keys.key_d && !e->keys.key_a))
	{
		vec->x += (e->keys.key_a) ? rx.x * speed : rx.x * -speed;
		vec->y += (e->keys.key_a) ? rx.y * speed : rx.y * -speed;
		vec->z += (e->keys.key_a) ? rx.z * speed : rx.z * -speed;
	}
	vec->y += (e->keys.key_plus && !e->keys.key_minus) ? 10 : 0;
	vec->y -= (e->keys.key_minus && !e->keys.key_plus) ? 10 : 0;
}

void			move_cam(t_rt *e, int speed)
{
	CCAM.rot.x += (e->keys.key_down && !e->keys.key_up) ? 1 : 0;
	CCAM.rot.x -= (e->keys.key_up && !e->keys.key_down) ? 1 : 0;
	CCAM.rot.y += (e->keys.key_right && !e->keys.key_left) ? 1 : 0;
	CCAM.rot.y -= (e->keys.key_left && !e->keys.key_right) ? 1 : 0;
	CCAM.rot.z += (e->keys.key_q && !e->keys.key_e) ? 1 : 0;
	CCAM.rot.z -= (e->keys.key_e && !e->keys.key_q) ? 1 : 0;
	CCAM.rot.x = (CCAM.rot.x > 360) ? 0 : CCAM.rot.x;
	CCAM.rot.x = (CCAM.rot.x < 0) ? 360 : CCAM.rot.x;
	CCAM.rot.y = (CCAM.rot.y > 360) ? 0 : CCAM.rot.y;
	CCAM.rot.y = (CCAM.rot.y < 0) ? 360 : CCAM.rot.y;
	CCAM.rot.z = (CCAM.rot.z > 360) ? 0 : CCAM.rot.z;
	CCAM.rot.z = (CCAM.rot.z < 0) ? 360 : CCAM.rot.z;
	if (!CCAM.is_circular && (e->keys.key_w || e->keys.key_s
	|| e->keys.key_a || e->keys.key_d || e->keys.key_plus || e->keys.key_minus))
		move(e, &CCAM.pos, speed);
	if (CCAM.is_circular && (e->keys.key_w || e->keys.key_s
	|| e->keys.key_a || e->keys.key_d || e->keys.key_plus || e->keys.key_minus))
	{
		CCAM.pos.x += (e->keys.key_d && !e->keys.key_a) ? 10 : 0;
		CCAM.pos.x -= (e->keys.key_a && !e->keys.key_d) ? 10 : 0;
		CCAM.pos.z += (e->keys.key_w && !e->keys.key_s) ? 10 : 0;
		CCAM.pos.z -= (e->keys.key_s && !e->keys.key_w) ? 10 : 0;
		CCAM.pos.y += (e->keys.key_plus && !e->keys.key_minus) ? 10 : 0;
		CCAM.pos.y -= (e->keys.key_minus && !e->keys.key_plus) ? 10 : 0;
	}
}*/