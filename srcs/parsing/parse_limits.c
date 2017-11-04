/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_limits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:07:34 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 19:07:35 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		parse_limit_node(t_limit *limit, xmlNodePtr node)
{
	xmlNodePtr	child;
	xmlChar		*val;

	if ((val = xmlGetProp(node, (xmlChar *)"radius")))
	{
		limit->r = ft_atof((char *)val);
		xmlFree(val);
	}
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
	new_limit.r = 0;
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
	while (lst)
	{
		obj->limit[i] = dispatch_limit_obj((xmlNodePtr)lst->content);
		lst = lst->next;
		i++;
	}
}

void			parse_limits(xmlNodePtr node_limits, t_obj *obj)
{
	t_list		*lst;
	t_list		*newlst;
	xmlNodePtr	temp;

	lst = NULL;
	temp = NULL;
	temp = node_limits->children;
	while (temp)
	{
		if (!ft_strequ((char *)temp->name, "text") &&
			!ft_strequ((char *)temp->name, "comment"))
		{
			newlst = ft_lstnew((void *)temp, sizeof(*temp));
			ft_lstpush(&lst, newlst);
		}
		temp = temp->next;
	}
	create_limit_obj(obj, lst);
	ft_lstfree(&lst);
}
