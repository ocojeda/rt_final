/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 17:12:35 by agfernan          #+#    #+#             */
/*   Updated: 2017/10/28 17:58:58 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstfree(t_list **lst)
{
	if (*lst)
	{
		ft_lstfree(&((*lst)->next));
		free(*lst);
		free((*lst)->content);
		*lst = NULL;
	}
}
