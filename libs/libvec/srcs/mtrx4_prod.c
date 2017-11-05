/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx4_prod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 04:26:18 by tfaure            #+#    #+#             */
/*   Updated: 2017/11/05 14:03:57 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

static void	prod_matrx4_p2(t_mtrx4 *matrix, t_mtrx4 a, t_mtrx4 b)
{
	(*matrix).mtrx[10] = a.mtrx[8] * b.mtrx[2] + a.mtrx[9] * b.mtrx[6]
			+ a.mtrx[10] * b.mtrx[10] + a.mtrx[11] * b.mtrx[14];
	(*matrix).mtrx[11] = a.mtrx[8] * b.mtrx[3] + a.mtrx[9] * b.mtrx[7]
			+ a.mtrx[10] * b.mtrx[11] + a.mtrx[11] * b.mtrx[15];
	(*matrix).mtrx[12] = a.mtrx[12] * b.mtrx[0] + a.mtrx[13] * b.mtrx[4]
			+ a.mtrx[14] * b.mtrx[8] + a.mtrx[15] * b.mtrx[12];
	(*matrix).mtrx[13] = a.mtrx[12] * b.mtrx[1] + a.mtrx[13] * b.mtrx[5]
			+ a.mtrx[14] * b.mtrx[9] + a.mtrx[15] * b.mtrx[13];
	(*matrix).mtrx[14] = a.mtrx[12] * b.mtrx[2] + a.mtrx[13] * b.mtrx[6]
			+ a.mtrx[14] * b.mtrx[10] + a.mtrx[15] * b.mtrx[14];
	(*matrix).mtrx[15] = a.mtrx[12] * b.mtrx[3] + a.mtrx[13] * b.mtrx[7]
			+ a.mtrx[14] * b.mtrx[11] + a.mtrx[15] * b.mtrx[15];
}

t_mtrx4		prod_matrx4(t_mtrx4 a, t_mtrx4 b)
{
	t_mtrx4		matrix;

	matrix.mtrx[0] = a.mtrx[0] * b.mtrx[0] + a.mtrx[1] * b.mtrx[4]
		+ a.mtrx[2] * b.mtrx[8] + a.mtrx[3] * b.mtrx[12];
	matrix.mtrx[1] = a.mtrx[0] * b.mtrx[1] + a.mtrx[1] * b.mtrx[5]
		+ a.mtrx[2] * b.mtrx[9] + a.mtrx[3] * b.mtrx[13];
	matrix.mtrx[2] = a.mtrx[0] * b.mtrx[2] + a.mtrx[1] * b.mtrx[6]
		+ a.mtrx[2] * b.mtrx[10] + a.mtrx[3] * b.mtrx[14];
	matrix.mtrx[3] = a.mtrx[0] * b.mtrx[3] + a.mtrx[1] * b.mtrx[7]
		+ a.mtrx[2] * b.mtrx[11] + a.mtrx[3] * b.mtrx[15];
	matrix.mtrx[4] = a.mtrx[4] * b.mtrx[0] + a.mtrx[5] * b.mtrx[4]
		+ a.mtrx[6] * b.mtrx[8] + a.mtrx[7] * b.mtrx[12];
	matrix.mtrx[5] = a.mtrx[4] * b.mtrx[1] + a.mtrx[5] * b.mtrx[5]
		+ a.mtrx[6] * b.mtrx[9] + a.mtrx[7] * b.mtrx[13];
	matrix.mtrx[6] = a.mtrx[4] * b.mtrx[2] + a.mtrx[5] * b.mtrx[6]
		+ a.mtrx[6] * b.mtrx[10] + a.mtrx[7] * b.mtrx[14];
	matrix.mtrx[7] = a.mtrx[4] * b.mtrx[3] + a.mtrx[5] * b.mtrx[7]
		+ a.mtrx[6] * b.mtrx[11] + a.mtrx[7] * b.mtrx[15];
	matrix.mtrx[8] = a.mtrx[8] * b.mtrx[0] + a.mtrx[9] * b.mtrx[4]
		+ a.mtrx[10] * b.mtrx[8] + a.mtrx[11] * b.mtrx[12];
	matrix.mtrx[9] = a.mtrx[8] * b.mtrx[1] + a.mtrx[9] * b.mtrx[5]
		+ a.mtrx[10] * b.mtrx[9] + a.mtrx[11] * b.mtrx[13];
	prod_matrx4_p2(&matrix, a, b);
	return (matrix);
}

t_vec3		vec_cpy3(t_vec3 origin)
{
	t_vec3	new;

	new = vec_new3(origin.x, origin.y, origin.z);
	return (new);
}
