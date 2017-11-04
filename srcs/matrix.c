/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:17:15 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 20:17:28 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		matrix_init(t_rt *e)
{
	t_mtrx4		transl;

	transl = transl_matrx4(CCAM.pos.x, CCAM.pos.y, CCAM.pos.z);
	CCAM.ctw = id_matrx4();
	CCAM.ctw = prod_matrx4(CCAM.ctw, rotz_matrx4(CCAM.rot.z));
	CCAM.ctw = prod_matrx4(CCAM.ctw, roty_matrx4(CCAM.rot.y));
	CCAM.ctw = prod_matrx4(CCAM.ctw, rotx_matrx4(CCAM.rot.x));
	CCAM.ctw = prod_matrx4(transl, CCAM.ctw);
}
