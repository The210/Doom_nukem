/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 19:49:09 by dhorvill          #+#    #+#             */
/*   Updated: 2018/11/07 20:41:59 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		**readmap(char *argv)
{
	int		fd;
	char	*buf;
	int		ret;
	char	**map;
	char	*str;

	str = ft_strnew(1);
	fd = open(argv, O_RDONLY);
	while ((ret = get_next_line(fd, &buf)) == 1)
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	if ((map = ft_strsplit(str, ' ')) == NULL
			|| ret == -1)
	{
		ft_putendl("Error: invalid file");
		return (NULL);
	}
	if (str)
		ft_strdel(&str);
	return (map);
}

t_player	init_player(t_player player)
{
	player.error = 0;
	player.dir.x = 0;
	player.dir.y = 1;
	player.plane.x = player.dir.y;
	player.plane.y = -player.dir.x;
	player.angularspeed = 0.07;
	player.speed = 0.1;
	player.pos.x = 7.501;
	player.pos.y = 5.501;
	return (player);
}
