/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 22:29:20 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/28 19:23:28 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		**read_squares(t_fd fd)
{
	char	*buf;
	int		ret;
	char	**walls;
	char	*str;

	str = ft_strnew(1);
	close(fd.walls);
	fd.walls = open("squares.txt", O_RDONLY);
	while ((ret = get_next_line(fd.walls, &buf)) == 1)
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	if ((walls = ft_strsplit(str, ' ')) == NULL || ret == -1)
	{
		ft_putendl("error");
		return (NULL);
	}
	if (str)
		ft_strdel(&str);
	return (walls);
}

t_wall		find_corners(char **walls, t_wall *w_coords, t_wall corners)
{
	int i;

	corners.start.x = w_coords[0].start.x;
	corners.start.y = w_coords[0].start.y;
	corners.end.x = w_coords[0].start.x;
	corners.end.y = w_coords[0].start.y;
	i = -1;
	while (++i < ft_tablen(walls))
	{
		corners.start.x = corners.start.x > w_coords[i].start.x ? w_coords[i].start.x : corners.start.x;	
		corners.start.x = corners.start.x > w_coords[i].end.x ? w_coords[i].end.x : corners.start.x;
		corners.end.x = corners.end.x < w_coords[i].start.x ? w_coords[i].start.x : corners.end.x;
		corners.end.x = corners.end.x < w_coords[i].end.x ? w_coords[i].end.x : corners.end.x;
		corners.start.y = corners.start.y > w_coords[i].start.y ? w_coords[i].start.y : corners.start.y;	
		corners.start.y = corners.start.y > w_coords[i].end.y ? w_coords[i].end.y : corners.start.y;
		corners.end.y = corners.end.y < w_coords[i].start.y ? w_coords[i].start.y : corners.end.y;
		corners.end.y = corners.end.y < w_coords[i].end.y ? w_coords[i].end.y : corners.end.y;
	}
	corners.start.x /= SCREEN_WIDTH / 75;
	corners.start.y /= SCREEN_HEIGHT / 75;
	corners.end.x /= SCREEN_WIDTH / 75;
	corners.end.y /= SCREEN_HEIGHT / 75;
	return (corners);
}

char	**populate_map(char **squares, char **map, t_coord corners)
{
	int i;
	int j;
	int count;

	i = -1;
	while (squares[++i])
	{
		j = 0;
		count = 0;
		while (squares[i][j])
		{
			while (squares[i][j] && squares[i][j] != '-' && (squares[i][j] < '0' || squares[i][j] > '9'))
				j++;
			if (map[i][j]
		}
	}
}

char	**create_map(t_fd fd, char **walls, t_wall *w_coords, char **map)
{
	t_wall	corners;
	int		i;
	int		j;
	char	**squares;

	corners = find_corners(walls, w_coords, corners);
	if ((map = (char**)malloc(sizeof(map) * (corners.end.y - corners.start.y + 1))) == 0)
		return NULL;
	map[corners.end.y - corners.start.y] = NULL;
	i = -1;
	while (++i < corners.end.y - corners.start.y)
	{
		if ((map[i] = (char*)malloc(sizeof(map[i]) * (corners.end.x - corners.start.x + 1))) == 0)
			return NULL;
		map[i][corners.end.x - corners.start.x] = '\0';
	}
	i = -1;
	while(++i < corners.end.y - corners.start.y)
	{
		j = -1;
		while (++j < corners.end.x - corners.start.x)
		{
			if (i == 0 || j == 0 || i == corners.end.y - corners.start.y - 1 || j == corners.end.x - corners.start.x - 1)
				map[i][j] = '1';
			else
				map[i][j] = '0';
		}
	}
	squares = read_squares(fd);
	map = populate_map(squares, map, corners);
	int keke = -1;
	while (map[++keke])
		printf("%s\n", map[keke]);
	return (map);
}
