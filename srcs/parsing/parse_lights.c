#include "rt.h"

t_light			parse_light(xmlNodePtr node)
{
	t_light		light;
	xmlChar		*val;
	xmlNodePtr	child;

	light.is_init = 0;
	if ((val = xmlGetProp(node, (xmlChar *)"intensity")))
	{
		light.intensity = atof((char *)val);
		xmlFree(val);
	}
	if ((child = has_child(node, "pos")))
		light.ray.pos = get_vec_from_node(child);
	if ((child = has_child(node, "color")))
		light.color = parse_color(child);
	return (light);
}

void			parse_lights(t_rt *e, t_list *lst)
{
	int		i;

	i = 0;
	if (!lst)
		return ;
	e->scene.nbr_light = ft_lstlen(lst);
	if (!e->scene.nbr_light)
		return ;
	while (lst)
	{
		e->scene.lights[i] = parse_light((xmlNodePtr)lst->content);
		lst = lst->next;
		i++;
	}
}
