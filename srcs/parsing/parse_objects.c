#include "rt.h"

static void		set_attrs(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, BAD_CAST"radius")))
	{
		obj->r = ft_atof((char *)val);
		xmlFree(val);
	}
	if ((val = xmlGetProp(node, BAD_CAST"shine")))
	{
		obj->mat.diff = ft_atof((char *)val);
		xmlFree(val);
	}
	if ((val = xmlGetProp(node, BAD_CAST"angle")))
	{
		obj->k = ft_atof((char *)val);
		xmlFree(val);
	}
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
		newlst = ft_lstnew((void *)temp, sizeof(*temp));
		ft_lstpush(&lst2, newlst);
		temp = temp->next;
	}
	create_obj(e, lst2);
	ft_lstfree(&lst2);
}
