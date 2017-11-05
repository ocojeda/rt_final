/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:08:33 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/05 15:56:42 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_camera(t_rt *e, xmlNodePtr node)
{
	xmlNodePtr	child;
	xmlChar		*val;

	if ((child = has_child(node, "pos")))
		e->scene.cam.pos = get_vec_from_node(child);
	if ((val = xmlGetProp(node, (xmlChar *)"fov")))
	{
		e->scene.cam.fov = ft_atoi((char *)val);
		xmlFree(val);
	}
	if ((child = has_child(node, "rot")))
		e->scene.cam.rot = get_vec_from_node(child);
	e->scene.cam.ratio_x = HAUTEUR / LARGEUR;
	e->scene.cam.ratio_y = LARGEUR / HAUTEUR;
	e->scene.cam.is_circular = 0;
}
