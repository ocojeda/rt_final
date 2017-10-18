#include "rtv1.h"

static t_color	get_pxl_color(t_rt *e, t_ray ray)
{
	t_reflect	ref;

	e->scene.id = -1;
	(void)ray;
//	if ((ref.min_dist = get_min_dist(e, ray)) == -1)
//		return (skybox(e, ray));
//	ref.tmp_id = e->scene.id;
//	ref.poi = vec_add3(ray.pos, vec_scale3(ray.dir, ref.min_dist));
//	ref.counter = NR_ITER;
//	ref.ray = c_ray(ray.pos, ray.dir);
//	ref.total_distance = 0;

	if (e->scene.id != -1)
	{
//		if (CMAT.reflex)
//			return (ret_reflected_pixel(e, ref, ray, 0));
//		if (CMAT.refract)
//		{
//			ref.color = get_color(e, CID, ref.poi);
//			e->scene.id = ref.tmp_id;
//			return (get_refracted_color(e, ref.poi, ref.color, ref));
//		}
//		if (CMAT.checker.l > 0)
//			return (get_checker_col(CMAT.checker, ref.poi));
//		return (get_color(e, CID, ref.poi));
	}
	/*printf("%f ",ray.dir.x);
	printf("%f ",ray.dir.y);
	printf("%f ",ray.dir.z);
	ft_putchar('\n');*/
	//ft_putnbr((int)e->scene.obj[1].color.r);
	ref.color = c_color(e->scene.obj[0].color.r, e->scene.obj[0].color.g, e->scene.obj[0].color.b);
	return (ref.color);
}

t_color			raytrace(int x, int y, t_rt *e)
{
	t_color		color;
	t_ray		ray;

	ray = ray_init(e, x * RES / ALIASING, y * RES / ALIASING);
	color = get_pxl_color(e, ray);
	(void)x;
	(void)e;
//    color = c_color(x,y,y); 
	return (color);
}