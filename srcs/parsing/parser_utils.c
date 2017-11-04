/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:08:19 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 19:08:20 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

xmlNodePtr		has_child(xmlNodePtr a_node, char *attr)
{
	xmlChar		*cast;
	xmlNodePtr	cur;

	cur = NULL;
	cur = a_node->children;
	cast = (xmlChar *)attr;
	while (cur)
	{
		if (!xmlStrcmp(cur->name, cast))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_color			parse_color(xmlNodePtr node)
{
	char		*str;
	int			r;
	int			g;
	int			b;

	str = (char *)xmlGetProp(node, (xmlChar *)"r");
	r = ft_atoi(str);
	xmlFree(str);
	str = (char *)xmlGetProp(node, (xmlChar *)"g");
	g = ft_atoi(str);
	xmlFree(str);
	str = (char *)xmlGetProp(node, (xmlChar *)"b");
	b = ft_atoi(str);
	xmlFree(str);
	return (c_color(r, g, b));
}

t_vec3			get_vec_from_node(xmlNodePtr node)
{
	t_vec3	new_vec;
	char	*str;

	str = (char *)(xmlGetProp(node, (xmlChar *)"x"));
	new_vec.x = ft_atof(str);
	xmlFree(str);
	str = (char *)(xmlGetProp(node, (xmlChar *)"y"));
	new_vec.y = ft_atof(str);
	xmlFree(str);
	str = (char *)(xmlGetProp(node, (xmlChar *)"z"));
	new_vec.z = ft_atof(str);
	xmlFree(str);
	return (new_vec);
}

void			get_nodes_by_name(xmlNodePtr cur, char *node_name, t_list **lst)
{
	t_list	*new_lst;

	while (cur)
	{
		if ((xmlStrEqual(cur->name, (xmlChar *)node_name)))
		{
			new_lst = ft_lstnew((void *)cur, sizeof(*cur));
			ft_lstpush(lst, new_lst);
		}
		get_nodes_by_name(cur->children, node_name, lst);
		cur = cur->next;
	}
}
