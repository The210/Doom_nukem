/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 22:29:20 by dhorvill          #+#    #+#             */
/*   Updated: 2018/11/13 20:38:46 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		write_map(t_fd fd, char **map)
{
	int	i;

	truncate ("map.txt", 0);
	i = -1;
	while (map[++i])
		ft_putendl_fd(map[i], fd.map);
}

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

t_wall		find_corners(char **walls, t_wall *w_coords)
{
	int i;
	t_wall scorners;

	scorners.start.x = w_coords[0].start.x;
	scorners.start.y = w_coords[0].start.y;
	scorners.end.x = w_coords[0].start.x;
	scorners.end.y = w_coords[0].start.y;
	i = -1;
	while (++i < ft_tablen(walls))
	{
		scorners.start.x = scorners.start.x > w_coords[i].start.x ? w_coords[i].start.x : scorners.start.x;	
		scorners.start.x = scorners.start.x > w_coords[i].end.x ? w_coords[i].end.x : scorners.start.x;
		scorners.end.x = scorners.end.x < w_coords[i].start.x ? w_coords[i].start.x : scorners.end.x;
		scorners.end.x = scorners.end.x < w_coords[i].end.x ? w_coords[i].end.x : scorners.end.x;
		scorners.start.y = scorners.start.y > w_coords[i].start.y ? w_coords[i].start.y : scorners.start.y;	
		scorners.start.y = scorners.start.y > w_coords[i].end.y ? w_coords[i].end.y : scorners.start.y;
		scorners.end.y = scorners.end.y < w_coords[i].start.y ? w_coords[i].start.y : scorners.end.y;
		scorners.end.y = scorners.end.y < w_coords[i].end.y ? w_coords[i].end.y : scorners.end.y;
	}
	scorners.start.x /= SCREEN_WIDTH / 75;
	scorners.start.y /= SCREEN_HEIGHT / 75;
	scorners.end.x /= SCREEN_WIDTH / 75;
	scorners.end.y /= SCREEN_HEIGHT / 75;
	//corners = &scorners;
	return (scorners);
}

char	**populate_map(char **squares, char **map, t_wall corners)
{
	int i;
	int j;
	int	x;
	int	y;
	int pol;
	char line;

	i = -1;
	pol = 1;
	while (squares[++i])
	{
		line = i % 26 + 65;
		j = 0;
		while (squares[i][j])
		{
			while (squares[i][j] && squares[i][j] != '-' && (squares[i][j] < '0' || squares[i][j] > '9'))
				j++;
			pol = pol == 1 ? 0 : 1;
			if (pol == 0)
			{
				x = ft_iatoi(squares[i], j);
				x -= corners.start.x;
			}
			else
			{
				y = ft_iatoi(squares[i], j);
				y -= corners.start.y;
			}
			while (squares[i][j] && ((squares[i][j] == '-') || (squares[i][j] >= '0' && squares[i][j] <= '9')))
				j++;
			if (pol == 1 && x < corners.end.x - corners.start.x && y < corners.end.y - corners.start.y && map[y][x] && (map[y][x] < 'A' || map[y][x] > 'Z') && map[y][x] != '1')
				map[y][x] = line;
			else if (pol == 1 && x < corners.end.x - corners.start.x && y < corners.end.y - corners.start.y && map[y][x] && ((map[y][x] >= 'A' && map[y][x] <= 'Z') || map[y][x] == '1'))
				map[y][x] = '+';
		}
	}
	return (map);
}

char	**create_map(t_fd fd, char **walls, t_wall *w_coords, char **map, t_wall *corners)
{
	int		i;
	int		j;
	char	**squares;
	t_wall	tmp_cor;

	tmp_cor = find_corners(walls, w_coords);
	corners = &tmp_cor;
	if ((map = (char**)malloc(sizeof(map) * (corners->end.y - corners->start.y + 2))) == 0)
		return NULL;
	map[corners->end.y - corners->start.y] = NULL;
	i = -1;
	while (++i < corners->end.y - corners->start.y)
	{
		if ((map[i] = (char*)malloc(sizeof(map[i]) * (corners->end.x - corners->start.x + 2))) == 0)
			return NULL;
		map[i][corners->end.x - corners->start.x] = '\0';
	}
	i = -1;
	while(++i < corners->end.y - corners->start.y)
	{
		j = -1;
		while (++j < corners->end.x - corners->start.x)
		{
			if (i == 0 || j == 0 || i == corners->end.y - corners->start.y - 1 || j == corners->end.x - corners->start.x - 1)
				map[i][j] = '1';
			else
				map[i][j] = '0';
		}
	}
	squares = read_squares(fd);
	map = populate_map(squares, map, *corners);
	return (map);
}
