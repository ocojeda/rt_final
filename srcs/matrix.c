/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:17:15 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/05 16:11:49 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		matrix_init(t_rt *e)
{
	t_mtrx4		transl;

	CCAM.rot.z = (CCAM.rot.z > 360) ? 0 : CCAM.rot.z;
	CCAM.rot.z = (CCAM.rot.z < 0) ? 360 : CCAM.rot.z;
	CCAM.rot.y = (CCAM.rot.y > 360) ? 0 : CCAM.rot.y;
	CCAM.rot.y = (CCAM.rot.y < 0) ? 360 : CCAM.rot.y;
	CCAM.rot.x = (CCAM.rot.x > 360) ? 0 : CCAM.rot.x;
	CCAM.rot.x = (CCAM.rot.x < 0) ? 360 : CCAM.rot.x;
	transl = transl_matrx4(CCAM.pos.x, CCAM.pos.y, CCAM.pos.z);
	CCAM.ctw = id_matrx4();
	CCAM.ctw = prod_matrx4(CCAM.ctw, rotz_matrx4(CCAM.rot.z));
	CCAM.ctw = prod_matrx4(CCAM.ctw, roty_matrx4(CCAM.rot.y));
	CCAM.ctw = prod_matrx4(CCAM.ctw, rotx_matrx4(CCAM.rot.x));
	CCAM.ctw = prod_matrx4(transl, CCAM.ctw);
}
