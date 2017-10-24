#include "../includes/rt.h"

t_ray			c_ray(t_vec3 i, t_vec3 j)
{
	t_ray		ray;

    ray.pos = vec_new3(i.x, i.y, i.z);
	ray.dir = vec_norme3(vec_new3(j.x, j.y, j.z));
	return (ray);
}

t_ray		ray_init(t_rt *e, int x, int y)
{
	t_ray	ray;
	t_vec3	px;
    float	fov;

	fov = tan(CCAM.fov / 2 * DEG2RAD);
	px = vec_new3((2 * (((float)x) / LARGEUR) - 1) * fov * CCAM.ratio_x,
		(1 - 2 * (((float)y) / HAUTEUR)) * fov * CCAM.ratio_y, 1);
	ray.pos = prod_vec3_matrx4(vec_new3(0, 0, 0), CCAM.ctw);
	px = prod_vec3_matrx4(px, CCAM.ctw);
	ray.dir = vec_norme3(vec_sub3(px, ray.pos));
	return (ray);
}

