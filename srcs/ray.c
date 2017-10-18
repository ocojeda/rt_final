# include "rtv1.h"

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
	//t_vec3	px;
    //float	fov;
    ray.pos = e->scene.cam.pos;
    ray.dir = vec_norme3(vec_sub3(vec_new3(x, y, 0), e->scene.cam.pos));

    /*<camera fov="45">
    <pos x="0" y="100" z="-1000"/>
    <dir x="0" y="0" z="0"/>
    */
    //fov = tan(CCAM.fov / 2 * DEG2RAD);
	//px = vec_new3((2 * ((x + 0.5) / LARGEUR) - 1) * fov * CCAM.ratio_x,
	//	(1 - 2 * ((y + 0.5) / HAUTEUR)) * fov * CCAM.ratio_y, 1);
	//ray.pos = prod_vec3_matrx4(vec_new3(0, 0, 0), CCAM.ctw);
	//px = prod_vec3_matrx4(px, CCAM.ctw);
	//ray.dir = vec_norme3(vec_sub3(px, ray.pos));
	//e->scene.max_iter = 3;
	return (ray);
}
