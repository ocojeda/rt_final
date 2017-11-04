/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:13:46 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 20:52:39 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_vec3			object_norm(t_obj obj, t_vec3 poi, t_vec3 cam, t_ray ray)
{
	t_vec3	norm;

	cam.x = cam.x;
	norm = vec_new3(0, 0, 0);
	if (obj.type == CYLINDER)
		norm = vec_norme3(cylinder_norm(obj, poi));
	else if (obj.type == SPHERE)
		norm = vec_norme3(sphere_norm(obj, poi));
	else if (obj.type == PLANE)
		norm = vec_norme3(plane_norm(obj));
	else if (obj.type == CONE)
		norm = vec_norme3(cone_norm(obj, poi));
	else if (obj.type == PARABOLOID)
		norm = vec_norme3(paraboloid_norm(obj, poi));
	return (norm);
}
