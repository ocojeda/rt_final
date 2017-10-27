#include "rt.h"

void		parse_camera(t_rt *e, xmlNodePtr node)
{
	xmlNodePtr	child;
	xmlChar			*val;	

	if ((child = has_child(node, "pos")))
		e->scene.cam.pos = get_vec_from_node(child);
	if ((val = xmlGetProp(node, (xmlChar *)"fov")))
	{
		e->scene.cam.fov = ft_atoi((char *)val);
		xmlFree(val);
	}
	e->scene.cam.ratio_x = HAUTEUR / LARGEUR;
	e->scene.cam.ratio_y = LARGEUR / HAUTEUR;
	e->scene.cam.is_circular = 0;
}
