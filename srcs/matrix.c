#include "../includes/rt.h"

void		matrix_init(t_rt *e)
{
	t_mtrx4		transl;

	transl = transl_matrx4(CCAM.pos.x, CCAM.pos.y, CCAM.pos.z);
	CCAM.ctw = id_matrx4();
	CCAM.ctw = prod_matrx4(CCAM.ctw, rotz_matrx4(CCAM.rot.z));
	CCAM.ctw = prod_matrx4(CCAM.ctw, roty_matrx4(CCAM.rot.y));
	CCAM.ctw = prod_matrx4(CCAM.ctw, rotx_matrx4(CCAM.rot.x));
	CCAM.ctw = prod_matrx4(CCAM.ctw, transl);
}