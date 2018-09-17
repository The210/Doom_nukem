/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:27:40 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/17 19:41:39 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

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

char	**flood_up(char **map, int i, int j, char wall, char flood, int *flag)
{
	int	x;
	int	y;

	x = j;
	y = i + 1;
	while (map[--y] && map[y][x] != wall)
	{
		if (map[y][x] != flood)
			*flag = 0;
		map[y][x] = flood;
	}
	return (map);
}

char	**flood_down(char **map, int i, int j, char wall, char flood, int *flag)
{
	int	x;
	int	y;

	x = j;
	y = i - 1;
	while (map[++y] && map[y][x] != wall)
	{
		if (map[y][x] != flood)
			*flag = 0;
		map[y][x] = flood;
	}
	return (map);
}

char	**flood_left(char **map, int i, int j, char wall, char flood, int *flag)
{
	int	x;
	int	y;

	x = j + 1;
	y = i;
	while (map[y][--x] && map[y][x] != wall)
	{
		if (map[y][x] != flood)
			*flag = 0;
		map[y][x] = flood;
	}
	return (map);
}

char	**flood_right(char **map, int i, int j, char wall, char flood, int *flag)
{
	int	x;
	int	y;

	x = j - 1;
	y = i;
	while (map[y] && map[y][++x] != wall)
	{
		if (map[y][x] != flood)
			*flag = 0;
		map[y][x] = flood;
	}
	return (map);
}

char	**flood_cross(char **map, int i, int j, char wall, char flood, int *flag)
{
	int x;
	int y;

	map = flood_up(map, i, j, wall, flood, flag);
	map = flood_down(map, i, j, wall, flood, flag);
	map = flood_right(map, i, j, wall, flood, flag);
	map = flood_left(map, i, j, wall, flood, flag);
	return (map);
}

char	**determine_rooms(char **map, int a, int b)
{
	int		i;
	int		j;
	int		flag;
	char	wall;
	char	flood;

	wall = 'w';
	flood = 'f';
	flag = 0;
	if (map[b][a] && map[b][a] != wall)
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
					map = flood_cross(map, i, j, wall, flood, &flag);
			}
		}
	}
	return (map);
}

int	main(int argc, char **argv)
{
	int fd;
	int ret;
	char **buf;

	buf = readmap(argv[1]);
	buf = determine_rooms(buf, atoi(argv[2]), atoi(argv[3]));
	ret = -1;
	while (buf[++ret])
		printf("%s\n", buf[ret]);
	return (0);
}
