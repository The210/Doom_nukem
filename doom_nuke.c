/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nuke.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:27:55 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/10 23:19:40 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"

void		ft_puttab(char **tab)
{
	int i = -1;
	while (tab[++i])
		ft_putendl(tab[i]);
}

int			check_key_down(t_wind wind)
{
	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(wind.window);
		SDL_Quit();
		return (0);
	}
	return (1);
}

int			ft_iatoi(char *wall, int index)
{
	int number;
	int i;

	i = index;
	number = 0;
	while (wall[i] && wall[i] >= '0' && wall[i] <= '9')
	{
		number = number * 10 + wall[i] - '0';
		i++;
	}
	return (number);
}

char		**read_lines(fd)
{
	char	*buf;
	int		ret;
	char	**walls;
	char	*str;

	str = ft_strnew(1);
	close(fd);
	fd = open("lines.txt", O_RDONLY);
	while ((ret = get_next_line(fd, &buf)) == 1)
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

t_wind		init_wind(t_wind wind)
{
	wind.screen = NULL;
	wind.window = SDL_CreateWindow("Doom_Nukem", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	wind.screen = SDL_GetWindowSurface(wind.window);
	return (wind);
}

t_wall		*separate_walls(char **walls)
{
	t_wall	*w_coords;
	int		count;
	int		i;
	int		j;

	i = -1;
	if ((w_coords = (t_wall*)malloc(sizeof(t_wall) * (ft_tablen(walls) + 1) * 100)) == 0)
		w_coords[0].error = 1;
	while (walls[++i])
	{
		j = 0;
		count = 0;
		while (walls[i][j])
		{
			while(walls[i][j] && (walls[i][j] < '0' || walls[i][j] > '9'))
				j++;
			if (count == 0)
				w_coords[i].start.x = ft_iatoi(walls[i], j);
			else if (count == 1)
				w_coords[i].start.y = ft_iatoi(walls[i], j);
			else if (count == 2)
				w_coords[i].end.x = ft_iatoi(walls[i], j);
			else if (count == 3)
				w_coords[i].end.y = ft_iatoi(walls[i], j);
			while (walls[i][j] && walls[i][j] >= '0' && walls[i][j] <= '9')
				j++;
			count++;
		}
	}
//	printf("%i, %i, %i %i\n", w_coords[0].start.x, w_coords[0].start.y, w_coords[0].end.x, w_coords[0].end.y);
	return (w_coords);
}

char		**ft_append(char **tab, char *s)
{
	char	**ss;
	int		i;
	int		j;

	if (!tab && !s)
		return (NULL);
	if (!tab)
	{
		ss = (char**)malloc(sizeof(ss) * 2);
		ss[0] = ft_strdup(s);
		ss[1] = NULL;
		return (ss);
	}
	if (!s)
		return (tab);
	if ((ss = (char**)malloc(sizeof(ss) * (ft_tablen(tab) + 2))) == 0)
		return (NULL);
	ss[ft_tablen(ss)] = NULL;
	i = -1;
	while (tab[++i])
		ss[i] = ft_strdup(tab[i]);
	ss[i] = ft_strdup(s);
	free(tab);
	return (ss);
}

void		re_draw_walls(int fd, t_wind wind, t_wall *w_coords, char **walls)
{
//	char	**walls;
//	t_wall	*w_coords;
	int		i;
	t_line	line;

	i = -1;
	//walls = read_lines(fd);
	//w_coords = separate_walls(walls);
	while (++i < ft_tablen(walls))
		ft_draw_line2(wind, w_coords[i].start, w_coords[i].end, line);
	//free(w_coords);
}

char		*get_last_line(int fd)
{
	char *buf;
	close (fd);
	open("lines.txt", O_RDONLY);
	while (get_next_line(fd, &buf))
		ft_strdel(&buf);
	close (fd);
	fd = open("lines.txt", O_RDWR | O_APPEND);
	return (buf);
}

char		**update_walls(char **walls, t_wall **w_coords, int fd, int flag)
{
	///if (flag == 1)
	//	walls = ft_append(walls, get_last_line(fd));
//	else
	walls = read_lines(fd);
	if (*w_coords)
		free(*w_coords);
	*w_coords = separate_walls(walls);
	return (walls);
}

void		write_l_coords(t_coord start, t_coord end, int fd)
{
	ft_putnbr_fd(start.x, fd);
	ft_putchar_fd('.', fd);
	ft_putnbr_fd(start.y, fd);
	ft_putchar_fd(':', fd);
	ft_putnbr_fd(end.x, fd);
	ft_putchar_fd('.', fd);
	ft_putnbr_fd(end.y, fd);
	ft_putchar_fd('\n', fd);
}

int			main(int argc, char **argv)
{
	t_player	player;
	t_wind		wind;
	t_line		line;
	t_texture	texture;
	char		**walls;
	t_wall		*w_coords;
	t_coord		mouse_pos;
	int			drawing;
	int			fd;
	int			flag;
	char		*buf;
	t_coord		start_line;

	drawing = 0;
	flag = 0;
	wind = init_wind(wind);
	mouse_pos.x = 0;
	mouse_pos.y = 0;
	fd = open("lines.txt", O_RDWR | O_APPEND);
	if (get_next_line(fd, &buf) != -1)
	{
		flag = 1;
		walls = update_walls(walls, &w_coords, fd, flag);
		re_draw_walls(fd, wind, w_coords, walls);
		ft_strdel(&buf);
	}
	close (fd);
	fd = open("lines.txt", O_CREAT | O_RDWR | O_APPEND);
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_KEYDOWN)
				if (check_key_down(wind) == 0)
				{
					close(fd);
					return (0);
				}
			if (wind.event.type == SDL_MOUSEMOTION)
			{
				if (drawing == 1)
				{
					SDL_FillRect(wind.screen, NULL, 0x000000);
					if (flag == 1)
					{
						re_draw_walls(fd, wind, w_coords, walls);
						close (fd);
						fd = open("lines.txt", O_RDWR | O_APPEND);
					}
				}
				mouse_pos.x = wind.event.motion.x;
				mouse_pos.y = wind.event.motion.y;
			}
			if (wind.event.type == SDL_MOUSEBUTTONDOWN)
			{
				start_line = mouse_pos;
				drawing = 1;
			}
			else if (wind.event.type == SDL_MOUSEBUTTONUP)
			{
				write_l_coords(start_line, mouse_pos, fd);
				walls = update_walls(walls, &w_coords, fd, flag);
				drawing = 0;
				flag = 1;
			}
			if (drawing == 1)
			   ft_draw_line2(wind, start_line, mouse_pos, line);
		}
		SDL_UpdateWindowSurface(wind.window);
	}
}
