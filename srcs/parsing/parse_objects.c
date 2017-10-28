#include "rt.h"

static void		default_value(t_obj *obj)
{
	obj->mat.refract = 0;
	obj->mat.reflex = 0;
	obj->mat.diff = 0.5;
	obj->neg = 0;
	obj->limit_active = 0;
	obj->limit_nbr = 0;
}

static void		parse_obj_node(t_obj *obj, xmlNodePtr node)
{
	xmlNodePtr	child;

	set_attrs(obj, node);
	if ((child = has_child(node, "pos")))
		obj->pos = get_vec_from_node(child);
	if ((child = has_child(node, "normal")))
		obj->vector = vec_norme3(get_vec_from_node(child));
	if ((child = has_child(node, "color")))
		obj->color = parse_color(child);
	if ((child = has_child(node, "limits")))
		parse_limits(child, obj);
}

static t_obj	dispatch_obj(xmlNodePtr node)
{
	t_obj		new_obj;

	if (xmlStrEqual(node->name, (xmlChar *)"sphere"))
		new_obj.type = SPHERE;
	else if (xmlStrEqual(node->name, (xmlChar *)"plane"))
		new_obj.type = PLANE;
	else if (xmlStrEqual(node->name, (xmlChar *)"cone"))
		new_obj.type = CONE;
	else if (xmlStrEqual(node->name, (xmlChar *)"cylinder"))
		new_obj.type = CYLINDER;
	else if (xmlStrEqual(node->name, (xmlChar *)"paraboloid"))
		new_obj.type = PARABOLOID;
	default_value(&new_obj);
	parse_obj_node(&new_obj, node);
	return (new_obj);
}

static void		create_obj(t_rt *e, t_list *lst)
{
	int i;

	i = 0;
	e->scene.nbr_obj = ft_lstlen(lst);
	if (e->scene.nbr_obj == 0)
		return ;
	e->scene.obj = (t_obj *)semalloc(sizeof(t_obj) * e->scene.nbr_obj);
	while (lst)
	{
		e->scene.obj[i] = dispatch_obj((xmlNodePtr)lst->content);
		lst = lst->next;
		i++;
	}
	e->scene.obj[i].type = END;
}

void			parse_objects(t_rt *e, t_list *lst)
{
	t_list		*lst2;
	t_list		*newlst;
	xmlNodePtr	temp;

	lst2 = NULL;
	temp = NULL;
	if (!lst)
		return ;
	temp = ((xmlNodePtr)lst->content)->children;
	while (temp)
	{
		if (!ft_strequ((char *)temp->name, "text") &&
			!ft_strequ((char *)temp->name, "comment"))
		{
			newlst = ft_lstnew((void *)temp, sizeof(*temp));
			ft_lstpush(&lst2, newlst);
		}
		temp = temp->next;
	}
	create_obj(e, lst2);
	ft_lstfree(&lst2);
}
