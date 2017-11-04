#include "../includes/rt.h"

int			damier(t_vec3 *pos, t_rt *e)
{
  int x = (int)pos->x;
  int y = (int)pos->y;
  int z = (int)pos->z;
  
  x = (int)((x + 13000) / 500);
  y = (int)(y / 500);
  z = (int)((z + 13000) / 500);
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