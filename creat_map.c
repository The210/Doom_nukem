/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 22:29:20 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/26 23:17:26 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wall		find_corners(char **walls, t_wall *w_coords, t_wall corner)
{
	int i;

	corner.start.x = 0;
	corner.start.y = 0;
	corner.end.x = 0;
	corner.end.y = 0;
	i = -1;
	while (++i < ft_tablen(walls))
	{
		corner.start.x = corner.start.x > w_coords[i].start.x ? w_coords[i].start.x : corner.start.x;	
		corner.start.x = corner.start.x > w_coords[i].end.x ? w_coords[i].end.x : corner.start.x;
		corner.end.x = corner.end.x < w_coords[i].start.x ? w_coords[i].start.x : corner.end.x;
		corner.end.x = corner.end.x < w_coords[i].end.x ? w_coords[i].end.x : corner.end.x;
		corner.start.y = corner.start.y > w_coords[i].start.y ? w_coords[i].start.y : corner.start.y;	
		corner.start.y = corner.start.y > w_coords[i].end.y ? w_coords[i].end.y : corner.start.y;
		corner.end.y = corner.end.y < w_coords[i].start.y ? w_coords[i].start.y : corner.end.y;
		corner.end.y = corner.end.y < w_coords[i].end.y ? w_coords[i].end.y : corner.end.y;
	}
	return (corner);
}

char	**create_map(t_fd fd, char **walls, t_wall *w_coords, char **map)
{
	t_wall	corners;
	int		i;
	int		j;

	corners = find_corners(walls, w_coords, corners);
	if ((map = (char**)malloc(sizeof(map) * (corners.end.y - corners.start.y + 1))) == 0)
		return NULL;
	map[corners.end.y - corners.start.y] = NULL;
	i = -1;
	while (map[++i])
	{
		if ((map[i] = (char*)malloc(sizeof(map[i]) * (corners.end.x - corners.start.x + 1))) == 0)
			return NULL;
		map[i][corners.end.x - corners.start.x] = '\0';
	}
	i = -1;
	while(map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (i == 0 || j == 0 || i == corners.end.y - corners.start.y - 1 || j == corners.end.x - corners.start.x - 1)
				map[i][j] = '1';
			else
				map[i][j] = '0';
		}
	}
	int keke = -1;
	while (map[++keke])
		printf("%s\n", map[keke]);
	return (map);
}
