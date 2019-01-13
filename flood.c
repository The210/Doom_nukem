/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:27:40 by dhorvill          #+#    #+#             */
/*   Updated: 2018/10/02 18:21:47 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char	**flood_up(char **map, int i, int j, char flood, int *flag)
{
	int	x;
	int	y;

	x = j;
	y = i + 1;
	while (--y >= 0 && (map[y][x] < 'A' || map[y][x] > 'Z') && map[y][x] != '+' && map[y][x] != '1')
	{
		if (map[y][x] != flood)
			*flag = 0;
		map[y][x] = flood;
	}
	return (map);
}

char	**flood_down(char **map, int i, int j, char flood, int *flag)
{
	int	x;
	int	y;

	x = j;
	y = i - 1;
	while (map[++y] && (map[y][x] < 'A' || map[y][x] > 'Z') && map[y][x] != '+' && map[y][x] != '1')
	{
		if (map[y][x] != flood)
			*flag = 0;
		map[y][x] = flood;
	}
	return (map);
}

char	**flood_left(char **map, int i, int j, char flood, int *flag)
{
	int	x;
	int	y;

	x = j + 1;
	y = i;
	while (map[y][--x] && (map[y][x] < 'A' || map[y][x] > 'Z') && map[y][x] != '+' && map[y][x] != '1')
	{
		if (map[y][x] != flood)
			*flag = 0;
		map[y][x] = flood;
	}
	return (map);
}

char	**flood_right(char **map, int i, int j, char flood, int *flag)
{
	int	x;
	int	y;

	x = j - 1;
	y = i;
	while (map[y][++x] && (map[y][x] < 'A' || map[y][x] > 'Z') && map[y][x] != '+' && map[y][x] != '1')
	{
		if (map[y][x] != flood)
			*flag = 0;
		map[y][x] = flood;
	}
	return (map);
}

char	**flood_cross(char **map, int i, int j, char flood, int *flag)
{
	int x;
	int y;

	map = flood_up(map, i, j, flood, flag);
	map = flood_down(map, i, j, flood, flag);
	map = flood_right(map, i, j, flood, flag);
	map = flood_left(map, i, j, flood, flag);
	return (map);
}

char	**determine_rooms(char **map, int a, int b, char flood)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	map[b][a] = flood;
	while (flag == 0)
	{
		flag = 1;
		i = -1;
		while (map[++i])
		{
			j = -1;
			while (map[i][++j])
			{
				if (map[i][j] == flood)
					map = flood_cross(map, i, j, flood, &flag);
			}
		}
	}
	return (map);
}

char	**flood_all(char **map, t_wall *corners)
{
	int		i;
	int		j;
	int		room;
	char	flood;

	flood = 'a';
	room = 1;
	i = -1;
	printf("Corners.start.x : %i   Corners.start.y : %i\nCorners.end.x : %i   Corners.end.y : %i\n", corners->start.x,corners->start.y, corners->end.x, corners->end.y);
	while (room)
	{
		room = 0;
		while (++i < corners->end.y - corners->start.y)
		{
			j = -1;
			while (++j < corners->end.x - corners->start.x)
			{
				if (i < corners->end.y - corners->start.y && j < corners->end.x - corners->start.x  && map[i][j] == '0')
				{
					map = determine_rooms(map, j, i, flood);
					room = 1;
					flood++;
				}
			}
		}
	}
	return (map);
}
