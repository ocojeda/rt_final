/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 02:42:54 by tfaure            #+#    #+#             */
/*   Updated: 2017/11/05 19:05:50 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec3d		vec_new3d(double x, double y, double z)
{
	t_vec3d		pts;

	pts.x = x;
	pts.y = y;
	pts.z = z;
	return (pts);
}

t_vec3d		vec_tsub3d(t_vec3d u, t_vec3d v)
{
	t_vec3d		pts;

	pts.x = (u.y * v.z) - (v.y * u.z);
	pts.y = (v.x * u.z) - (u.x * v.z);
	pts.z = (u.x * v.y) - (v.x * u.y);
	return (pts);
}

t_vec3		vec_tsub3(t_vec3 u, t_vec3 v)
{
	t_vec3		pts;

	pts.x = (u.y * v.z) - (v.y * u.z);
	pts.y = (v.x * u.z) - (u.x * v.z);
	pts.z = (u.x * v.y) - (v.x * u.y);
	return (pts);
}

t_vec3d		vec_inv3d(t_vec3d u)
{
	t_vec3d		pts;

	pts.x = -u.x;
	pts.y = -u.y;
	pts.z = -u.z;
	return (pts);
}

t_vec3d		vec_norme3d(t_vec3d u)
{
	t_vec3d		pts;
	double		magnitude;

	magnitude = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
	if (magnitude > 0)
	{
		pts.x = u.x / magnitude;
		pts.y = u.y / magnitude;
		pts.z = u.z / magnitude;
		pts.m = magnitude;
		return (pts);
	}
	return (u);
}
