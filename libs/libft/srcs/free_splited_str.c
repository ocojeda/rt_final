/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splited_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:44:41 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 21:22:30 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		free_splited_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
		ft_memdel((void **)&str[i++]);
	ft_memdel((void **)&str);
}
