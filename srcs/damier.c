#include "../includes/rt.h"

int			damier(t_vec3 *pos, t_rt *e)
{
  int x;
  int y;
  int z;


  x = (int)((pos->x + 1100) / 500);
  y = (int)((pos->y + 700) / 500);
  z = (int)((pos->z + 1100) / 500);
  if (x % 2 == 0)
    {
      if (((y % 2 == 0) && (z % 2 == 0)) ||
	  (((y % 2 != 0) && (z % 2 != 0))))
	return (0);
      else
	return (1);
    }
  else
    {
      if ((((y % 2 == 0) && (z % 2 == 0))) ||
	  (((y % 2 != 0) && (z % 2 != 0))))
	return (1);
      else
	return (0);
	  }
}
