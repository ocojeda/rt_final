/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_ssp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:22:24 by mhalit            #+#    #+#             */
/*   Updated: 2017/10/20 19:20:45 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec3		vec_tsub3(t_vec3 u, t_vec3 v)
{
	t_vec3 pts;

	pts.x = (u.y * v.z) - (v.y * u.z);
	pts.y = (v.x * u.z) - (u.x * v.z);
	pts.z = (u.x * v.y) - (v.x * u.y);
	return (pts);
}

float		vec_dot3(t_vec3 u, t_vec3 v)
{
	float	dot;

	dot = u.x * v.x + u.y * v.y + u.z * v.z;
	return (dot);
}

t_vec3		vec_inv3(t_vec3 u)
{
	t_vec3 pts;

	pts.x = -u.x;
	pts.y = -u.y;
	pts.z = -u.z;
	return (pts);
}

t_vec3		vec_norme3(t_vec3 u)
{
	float	magnitude;
	t_vec3	pts;

	magnitude = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
	pts.x = u.x / magnitude;
	pts.y = u.y / magnitude;
	pts.z = u.z / magnitude;
	pts.m = magnitude;
	return (pts);
}

t_vec3		vec_scale3(t_vec3 u, float r)
{
	return (t_vec3){u.x * r, u.y * r, u.z * r, u.m};
}
