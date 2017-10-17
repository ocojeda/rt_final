/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:47:24 by mhalit            #+#    #+#             */
/*   Updated: 2017/09/30 10:47:26 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			checkn(char **reste, char **line, char *buf)
{
	char			*tmp;
	char			*fr;

	if (buf)
	{
		tmp = *reste;
		*reste = ft_strjoin(*reste, buf);
		free(tmp);
	}
	if ((tmp = ft_strchr(*reste, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*reste);
		fr = *reste;
		*reste = ft_strdup(tmp + 1);
		free(fr);
		return (1);
	}
	return (0);
}

int					get_next_line(int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static	char	*reste = NULL;
	int				i;

	if (!reste)
		reste = ft_strnew(BUFF_SIZE);
	if (checkn(&reste, line, NULL))
		return (1);
	while ((i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (checkn(&reste, line, buf))
			return (1);
	}
	if (i == -1)
		return (-1);
	if (reste && ft_strcmp(reste, "") != 0)
	{
		*line = ft_strdup(reste);
		free(reste);
		reste = NULL;
		return (1);
	}
	return (0);
}
