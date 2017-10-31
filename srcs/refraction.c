#include "../includes/rt.h"
t_ray			get_refracted_ray(t_rt *e, t_ray rayon, t_vec3 poi)
{
	t_vec3		normale;
	t_ray		ray;

	ray.pos = poi;
	normale = color_norm(e->scene.obj[e->scene.id], poi, e->scene.cam.pos);
	ray.dir = vec_add3(vec_scale3(normale, e->scene.obj[e->scene.id].mat.refract_rate * 
		(vec_dot3(rayon.dir, normale))), rayon.dir);
	return (ray);
}

static void		g_norme(t_rt *e, t_reflect *ref, t_norme *n, t_vec3 poi)
{
    ref->counter--;
    if(e->scene.obj[e->scene.id].mat.reflex)
    {  
        ref->new_ray = get_reflected_ray(e, ref->ray, poi);
        n->taux_temp = e->scene.obj[e->scene.id].mat.reflex;
    }
    else
    {
        ref->new_ray = get_refracted_ray(e, ref->ray, poi);
        n->taux_temp += e->scene.obj[e->scene.id].mat.refract;
    }
	ref->min_dist = find_min_dist_for_refref(e, &n->a, ref->new_ray);
	ref->total_distance += ref->min_dist;
	n->distance_rate = ft_map(ref->min_dist, ref->total_distance, 0, 1)
		* n->taux_temp;
}

void			prepare_refraction(t_rt *e, t_color *base_color,
		t_norme *n, t_reflect *ref)
{
	n->newpoi = vec_add3(ref->new_ray.pos, vec_scale3(ref->new_ray.dir,
	ref->min_dist));
	//ref->poi = n->newpoi;
	n->final_color = get_color(e, e->scene.obj[n->a], n->newpoi, ref->new_ray);
	*base_color = ft_map_color(*base_color, n->final_color, n->taux_temp);
	e->scene.id = n->a;
}


t_color			get_refracted_color(t_rt *e, t_vec3 poi, t_color base_color,
	t_reflect ref)
{
		t_norme		n;
	
		if (ref.counter == 0)
			return (base_color);
		g_norme(e, &ref, &n, poi);
		if (ref.min_dist < DIST_MAX)
		{
			prepare_refraction(e, &base_color, &n, &ref);
			ref.ray = c_ray(poi, ref.new_ray.dir);
            if (e->scene.obj[n.a].mat.refract)
			{
				n.temp_color1 = get_refracted_color(e, n.newpoi, base_color, ref);
                return (ft_map_color(base_color, n.temp_color1, 1 - n.distance_rate));
			}
            else if (e->scene.obj[n.a].mat.reflex)
            {
                n.temp_color1 = get_refracted_color(e, n.newpoi, base_color, ref);
                return (ft_map_color(base_color, n.temp_color1, 1 - n.distance_rate));
            }
			return (ft_map_color(base_color, n.final_color, n.distance_rate));
		}
		//return (base_color);
		return (ft_map_color(base_color, c_color(0,0,0), n.taux_temp));
}