#include "../includes/rt.h"

static int	g_tab[512] = {-1};

double	fade(double curve)
{
  return (curve * curve * curve * (curve * (curve * 6 - 15) + 10));
}

double	perl(double curve, double a, double b)
{
  return (a + curve * (b - a));

}

void	init_noise(int *c_unit, double *x, double *y, double *z)
{
  c_unit[0] = (int)floor(*x) & 255;
  c_unit[1] = (int)floor(*y) & 255;
  c_unit[2] = (int)floor(*z) & 255;
  *x -= floor(*x);
  *y -= floor(*y);
  *z -= floor(*z);
}

void	init_permutation()
{
  int	i;

  i = 0;
  while (i < 256)
    {
      g_tab[i] = rand() % 256;
      g_tab[256 + i] = g_tab[i];
      ++i;
    }
}

double		grad(int hash, double x, double y, double z)
{
  int		h;
  double	vec1;
  double	vec2;

  h = hash & 15;
  if (h < 8 || h == 12 || h == 13)
    vec1 = x;
  else
    vec1 = y;
  if (h < 4 || h == 12 || h == 13)
    vec2 = y;
  else
    vec2 = z;
  return (((h & 1) == 0 ? vec1 : -vec1) + ((h & 2) == 0 ? vec2 : -vec2));
}

double		get_perlin(double x, double y, double z)
{
  double	vec[3];
  int		c_unit[3];
  int		coor[6];

  if (g_tab[0] == -1)
    init_permutation();
  init_noise(c_unit, &x, &y, &z);
  vec[0] = fade(x);
  vec[1] = fade(y);
  vec[2] = fade(z);
  coor[0] = g_tab[c_unit[0]] + c_unit[1];
  coor[1] = g_tab[coor[0]] + c_unit[2];
  coor[2] = g_tab[coor[0] + 1] + c_unit[2];
  coor[3] = g_tab[c_unit[0] + 1] + c_unit[1];
  coor[4] = g_tab[coor[3]] + c_unit[2];
  coor[5] = g_tab[coor[3] + 1] + c_unit[2];
  return (perl(vec[2], perl(vec[1], perl(vec[0], grad(g_tab[coor[1]], x, y, z),
					 grad(g_tab[coor[4]], x - 1, y, z)),
			    perl(vec[0], grad(g_tab[coor[2]], x, y - 1, z),
				 grad(g_tab[coor[5]], x - 1, y - 1, z))),
	       perl(vec[1], perl(vec[0], grad(g_tab[coor[1] + 1], x, y, z - 1),
				 grad(g_tab[coor[4] + 1], x - 1, y, z - 1)),
		    perl(vec[0], grad(g_tab[coor[2] + 1], x, y - 1, z - 1),
			 grad(g_tab[coor[5] + 1], x - 1, y - 1, z - 1)))));
}

t_color	bruit(float valeur, t_color c1, t_color c2, float seuil) 
{
	t_color resultat;
	double f;

    if(valeur > seuil / 2)
        valeur = seuil - valeur;
	f = (1 - cos(PI * valeur / (seuil / 2))) / 2;
	
	resultat.r = c1.r * (1 - f) + c2.r * f;
    resultat.g = c1.g * (1 - f) + c2.g * f;
    resultat.b = c1.b * (1 - f) + c2.b * f;
    return resultat;
}

t_color	bruit2(float valeur, t_color c1, t_color c2, float x) 
{
	t_color resultat;
	double f;
	double seuil;

	seuil = 1000;
    if(valeur > seuil / 2)
        valeur = seuil - valeur * x;
	f = (1 - cos(PI * valeur / (seuil / 2))) / 2;
	
	resultat.r = c1.r * (1 - f) + c2.r * f;
    resultat.g = c1.g * (1 - f) + c2.g * f;
    resultat.b = c1.b * (1 - f) + c2.b * f;
    return resultat;
}

float bruit_coherent(float x, float y, float persistance) 
{
    float somme = 0;
    float p = 1;
    int f = 1;
    int i;

	for(i = 0 ; i < x; i++) 
	{
        somme += p * sqrt((x * f / y * f));
        p *= persistance;
        f *= 2;
    }
    return somme * (1 - persistance) / (1 - p);
}

t_color	bruit3(float valeur, int x, int y, t_rt *e) 
{
	t_color resultat;
	double seuil;

	(void)e;

	seuil = 100;
	if(valeur > seuil / 2)
	valeur = seuil - valeur * (x * y);

	t_color c2 = c_color(70, 70, 70); // Gris clair
	t_color c1 = c_color(100, 100, 100); // Blanc

	valeur = -sqrt(fabs(sin(2 * 3.141592 * bruit_coherent(x,y,-1))));
    resultat.r = c1.r * (1 - valeur) + c2.r * valeur;
    resultat.g = c1.g * (1 - valeur) + c2.g * valeur;
	resultat.b = c1.b * (1 - valeur) + c2.b * valeur;
    return resultat;
}