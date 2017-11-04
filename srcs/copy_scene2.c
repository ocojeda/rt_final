/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_scene2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocojeda- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:34:26 by ocojeda-          #+#    #+#             */
/*   Updated: 2017/11/04 20:34:34 by ocojeda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_light				copy_light(t_light light)
{
	t_light			copy;

	copy.is_init = light.is_init;
	copy.ray = light.ray;
	copy.color = light.color;
	copy.intensity = light.intensity;
	return (copy);
}
