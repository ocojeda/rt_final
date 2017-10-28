#include "rt.h"

static void		parse_limit_node(t_limit *limit, xmlNodePtr node)
{
	xmlNodePtr	child;

	set_attrs_limits(limit, node);
	if ((child = has_child(node, "pos")))
		limit->pos = get_vec_from_node(child);
	if ((child = has_child(node, "normal")))
		limit->vector = vec_norme3(get_vec_from_node(child));
}

static t_limit	dispatch_limit_obj(xmlNodePtr node)
{
	t_limit		new_limit;

	if (xmlStrEqual(node->name, (xmlChar *)"limit_sphere"))
		new_limit.type = SPHERE;
	else if (xmlStrEqual(node->name, (xmlChar *)"limit_plane"))
		new_limit.type = PLANE;
	parse_limit_node(&new_limit, node);
	return (new_limit);
}

static void		create_limit_obj(t_obj *obj, t_list *lst)
{
	int i;

	i = 0;
	obj->limit_nbr = ft_lstlen(lst);
	if (obj->limit_nbr == 0)
		return ;
	obj->limit_active = 1;
	obj->limit = (t_limit *)semalloc(sizeof(t_limit) * obj->limit_nbr);
	while (lst)
	{
		obj->limit[i] = dispatch_limit_obj((xmlNodePtr)lst->content);
		lst = lst->next;
		i++;
	}
}

void			parse_limits(t_obj *obj, t_list *lst)
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
	create_limit_obj(obj, lst2);
	ft_lstfree(&lst2);
}
