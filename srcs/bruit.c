/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:14:22 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 19:20:21 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_color		bruit(float valeur, t_color c1, t_color c2, float seuil)
{
	t_color	resultat;
	double	f;

	if (valeur > seuil / 2)
		valeur = seuil - valeur;
	f = (1 - cos(PI * valeur / (seuil / 2))) / 2;
	resultat.r = c1.r * (1 - f) + c2.r * f;
	resultat.g = c1.g * (1 - f) + c2.g * f;
	resultat.b = c1.b * (1 - f) + c2.b * f;
	return (resultat);
}

t_color		bruit2(float valeur, t_color c1, t_color c2, float x)
{
	t_color	resultat;
	double	f;
	double	seuil;

	seuil = 1000;
	if (valeur > seuil / 2)
		valeur = seuil - valeur * x;
	f = (1 - cos(PI * valeur / (seuil / 2))) / 2;
	resultat.r = c1.r * (1 - f) + c2.r * f;
	resultat.g = c1.g * (1 - f) + c2.g * f;
	resultat.b = c1.b * (1 - f) + c2.b * f;
	return (resultat);
}

float		bruit_coherent(float x, float y, float persistance)
{
	float	somme;
	float	p;
	int		f;
	int		i;

	p = 1;
	f = 1;
	somme = 0;
	i = 0;
	while (i < x)
	{
		somme += p * sqrt((x * f / y * f));
		p *= persistance;
		f *= 2;
		i++;
	}
	return (somme * (1 - persistance) / (1 - p));
}

t_color		bruit3(float valeur, int x, int y)
{
	t_color	resultat;
	t_color	c1;
	t_color	c2;
	double	seuil;

	seuil = 100;
	if (valeur > seuil / 2)
		valeur = seuil - valeur * (x * y);
	c2 = c_color(70, 70, 70);
	c1 = c_color(100, 100, 100);
	valeur = -sqrt(fabs(sin(2 * 3.141592 * bruit_coherent(x, y, -1))));
	resultat.r = c1.r * (1 - valeur) + c2.r * valeur;
	resultat.g = c1.g * (1 - valeur) + c2.g * valeur;
	resultat.b = c1.b * (1 - valeur) + c2.b * valeur;
	return (resultat);
}
