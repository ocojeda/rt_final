/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 13:14:14 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/28 23:29:30 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec3	vec_new3(float x, float y, float z)
{
	t_vec3 pts;

	pts.x = x;
	pts.y = y;
	pts.z = z;
	return (pts);
}

t_vec3	vec_mul3(t_vec3 u, t_vec3 v)
{
	t_vec3 pts;

	pts.x = u.x * v.x;
	pts.y = u.y * v.y;
	pts.z = u.z * v.z;
	return (pts);
}

t_vec3	vec_div3(t_vec3 u, t_vec3 v)
{
	t_vec3 pts;

	pts.x = u.x / v.x;
	pts.y = u.y / v.y;
	pts.z = u.z / v.z;
	return (pts);
}

t_vec3	vec_add3(t_vec3 u, t_vec3 v)
{
	t_vec3 pts;

	pts.x = u.x + v.x;
	pts.y = u.y + v.y;
	pts.z = u.z + v.z;
	return (pts);
}

t_vec3	vec_sub3(t_vec3 u, t_vec3 v)
{
	t_vec3 pts;

	pts.x = u.x - v.x;
	pts.y = u.y - v.y;
	pts.z = u.z - v.z;
	return (pts);
}
