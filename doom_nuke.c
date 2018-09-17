/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nuke.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:27:55 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/18 00:31:40 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"

void	ft_puttab_fd(char **tab, int fd)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		ft_putstr_fd(tab[i], fd);
		ft_putchar_fd('\n', fd);
	}
}

void	check_key_up(t_wind wind, int *ctrl, int *drawing, int *shift, int *delete)
{
	if (wind.event.key.keysym.sym == SDLK_LCTRL)
		*ctrl = 0;
	if (wind.event.key.keysym.sym == SDLK_LSHIFT)
		*shift = 0;
	if (wind.event.key.keysym.sym == SDLK_p)
		*delete = 1;
}

void		ft_puttab(char **tab)
{
	int i = -1;
	while (tab[++i])
		ft_putendl(tab[i]);
}

int			check_key_down(t_wind wind, int *ctrl, int *drawing, int *shift, int select, t_wall *w_coords, char **walls)
{
	char *tmp;

	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(wind.window);
		SDL_Quit();
		return (0);
	}
	if (wind.event.key.keysym.sym == SDLK_LCTRL)
	{
		*ctrl = 1;
		*drawing = 0;
	}
	if (wind.event.key.keysym.sym == SDLK_LSHIFT)
	{
		*shift = 1;
		*drawing = 0;
	}
	return (1);
}

int			ft_iatoi(char *wall, int index)
{
	int number;
	int i;
	int	negative;

	i = index;
	negative = 1;
	number = 0;
	if (wall[index] == '-')
	{
		i++;
		negative = -1;
	}
	while (wall[i] && wall[i] >= '0' && wall[i] <= '9')
	{
		number = number * 10 + wall[i] - '0';
		i++;
	}
	return (number * negative);
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
			while(walls[i][j] && (walls[i][j] != '-' && (walls[i][j] < '0' || walls[i][j] > '9')))
				j++;
			if (count == 0)
				w_coords[i].start.x = ft_iatoi(walls[i], j);
			else if (count == 1)
				w_coords[i].start.y = ft_iatoi(walls[i], j);
			else if (count == 2)
				w_coords[i].end.x = ft_iatoi(walls[i], j);
			else if (count == 3)
				w_coords[i].end.y = ft_iatoi(walls[i], j);
			while (walls[i][j] && ((walls[i][j] >= '0' && walls[i][j] <= '9') || walls[i][j] == '-'))
				j++;
			count++;
		}
	}
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

void		re_draw_walls(int fd, t_wind wind, t_wall *w_coords, char **walls, t_coord map_offset)
{
	int		i;
	t_line	line;

	i = -1;
	line.offset = map_offset;
	line.color = 0xffffff;
	while (++i < ft_tablen(walls))
		ft_draw_line2(wind, w_coords[i].start, w_coords[i].end, line);
}

void		draw_select(int fd, t_wind wind, t_wall w_coords, t_coord map_offset)
{
	t_line line;

	line.color = 0xffff00;
	line.offset = map_offset;
	ft_draw_line2(wind, w_coords.start, w_coords.end, line);
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
	walls = read_lines(fd);
	if (*w_coords)
		free(*w_coords);
	*w_coords = separate_walls(walls);
	return (walls);
}

void		write_l_coords(t_coord start, t_coord end, int fd, t_coord offset)
{
	ft_putnbr_fd(start.x - offset.x, fd);
	ft_putchar_fd('.', fd);
	ft_putnbr_fd(start.y - offset.y, fd);
	ft_putchar_fd(':', fd);
	ft_putnbr_fd(end.x - offset.x, fd);
	ft_putchar_fd('.', fd);
	ft_putnbr_fd(end.y - offset.y, fd);
	ft_putchar_fd('\n', fd);
}

t_coord		snap_line(char **walls, t_wall *w_coords, t_coord mouse_pos, t_coord map_offset)
{
	int		i;
	t_coord	start_line;
	
	i = -1;
	start_line.x = mouse_pos.x;
	start_line.y = mouse_pos.y;

	if (walls)
	{
		while (++i < ft_tablen(walls))
		{
			if (sqrt(pow(map_offset.x + w_coords[i].start.x - mouse_pos.x, 2) + pow(map_offset.y + w_coords[i].start.y - mouse_pos.y, 2)) < 10)
			{
				start_line.x = w_coords[i].start.x + map_offset.x;
				start_line.y = w_coords[i].start.y + map_offset.y;
				break ;
			}
			if (sqrt(pow(map_offset.x + w_coords[i].end.x - mouse_pos.x, 2) + pow(map_offset.y + w_coords[i].end.y - mouse_pos.y, 2)) < 10)
			{
				start_line.x = w_coords[i].end.x + map_offset.x;
				start_line.y = w_coords[i].end.y + map_offset.y;
				break ;
			}
		}
	}
	return (start_line);
}

int		in_line(t_coord mouse_pos, t_coord map_offset, t_wall w_coord)
{
	t_coord dir;
	t_coord r_pos;
	t_coord true_pos;
	
	true_pos.x = mouse_pos.x - map_offset.x;
	true_pos.y = mouse_pos.y - map_offset.y;
	dir.x = w_coord.end.x - w_coord.start.x > 0 ? 1 : -1;
	dir.y = w_coord.end.y - w_coord.start.y > 0 ? 1 : -1;
	r_pos.x = true_pos.x - w_coord.start.x > 0 ? 1 : -1;
	r_pos.y = true_pos.y - w_coord.start.y > 0 ? 1 : -1;
	if (dir.x != r_pos.x || dir.y != r_pos.y)
		return (0);
	dir.x = w_coord.start.x - w_coord.end.x > 0 ? 1 : -1;
	dir.y = w_coord.start.y - w_coord.end.y > 0 ? 1 : -1;
	r_pos.x = true_pos.x - w_coord.end.x > 0 ? 1 : -1;
	r_pos.y = true_pos.y - w_coord.end.y > 0 ? 1 : -1;
	if (dir.x != r_pos.x || dir.y != r_pos.y)
		return (0);
	return (1);

}

int		select_wall(t_coord mouse_pos, char **walls, t_wall *w_coords, t_coord map_offset)
{
	int distance;
	int i;
	int check;

	i = -1;
	check = -1;
	if (walls)
	{
		while (++i < ft_tablen(walls))
		{
			distance = (abs((w_coords[i].end.y - w_coords[i].start.y) * (mouse_pos.x - map_offset.x) - (w_coords[i].end.x - w_coords[i].start.x) * (mouse_pos.y - map_offset.y) + (w_coords[i].end.x * w_coords[i].start.y) - (w_coords[i].end.y * w_coords[i].start.x)) / (sqrt(pow(w_coords[i].end.y - w_coords[i].start.y, 2) + pow(w_coords[i].end.x - w_coords[i].start.x, 2))));
			if (distance < 10)
			{
				if (in_line(mouse_pos, map_offset, w_coords[i]))
				{
					check = i;
					break ;
				}
			}
		}
	}
	return (check);
}

int			check_select(int shift, int select, t_coord mouse_pos, char **wals, t_wall *w_coords, t_coord map_offset)
{
	int distance;

	if (select != -1 && shift == 0)
	{
		distance = (abs((w_coords[select].end.y - w_coords[select].start.y) * (mouse_pos.x - map_offset.x) - (w_coords[select].end.x - w_coords[select].start.x) * (mouse_pos.y - map_offset.y) + (w_coords[select].end.x * w_coords[select].start.y) - (w_coords[select].end.y * w_coords[select].start.x)) / (sqrt(pow(w_coords[select].end.y - w_coords[select].start.y, 2) + pow(w_coords[select].end.x - w_coords[select].start.x, 2))));
		if (distance > 10 || in_line(mouse_pos, map_offset, w_coords[select]) == 0)
			select = -1;
	}
	return (select);
}

void		change_fd(int fd, t_wall *w_coords, char **walls, int *select, int *delete)
{
	int i;


	close(fd);
	fd = open("lines.txt", O_RDWR | O_APPEND);
	truncate("lines.txt", 0);
	close(fd);
	fd = open("lines.txt", O_RDWR | O_APPEND);
	i = -1;
	while (++i < ft_tablen(walls))
	{
		if (!(*delete == 1 && i == *select))
		{
			ft_putnbr_fd(w_coords[i].start.x, fd);
			ft_putchar_fd('.', fd);
			ft_putnbr_fd(w_coords[i].start.y, fd);
			ft_putchar_fd(':', fd);
			ft_putnbr_fd(w_coords[i].end.x, fd);
			ft_putchar_fd('.', fd);
			ft_putnbr_fd(w_coords[i].end.y, fd);
			ft_putchar_fd('\n', fd);
		}
		if (*delete == 1 && i == *select)
		{
			*select = -1;
			*delete = 0;
		}
	}
}

t_wall		*move_line(char **walls, t_wall *w_coords, t_coord mouse_pos, t_coord past_pos, int *select, t_coord map_offset, int fd, int *delete)
{
	t_coord movement;
	movement.x = mouse_pos.x - past_pos.x;
	movement.y = mouse_pos.y - past_pos.y;
	if (sqrt(pow(map_offset.x + w_coords[*select].start.x - mouse_pos.x, 2) + pow(map_offset.y + w_coords[*select].start.y - mouse_pos.y, 2)) < 20)
	{
		w_coords[*select].start.x += movement.x;
		w_coords[*select].start.y += movement.y;
	}
	else if (sqrt(pow(map_offset.x + w_coords[*select].end.x - mouse_pos.x, 2) + pow(map_offset.y + w_coords[*select].end.y - mouse_pos.y, 2)) < 20)
	{
		w_coords[*select].end.x += movement.x;
		w_coords[*select].end.y += movement.y;
	}
	else
	{
		w_coords[*select].start.x += movement.x;
		w_coords[*select].start.y += movement.y;
		w_coords[*select].end.x += movement.x;
		w_coords[*select].end.y += movement.y;
	}
	change_fd(fd, w_coords, walls, select, delete);
	return (w_coords);
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
	t_coord		offset;
	t_coord		map_offset;
	int			select;
	t_coord		past_pos;
	int			drawing;
	int			fd;
	int			flag;
	char		*buf;
	int			bleh;
	int			ctrl;
	int			a;
	int			shift;
	int			msbutton;
	int			delete;
	t_coord		start_line;
	t_coord		end_line;

	drawing = 0;
	flag = 0;
	select = -1;
	bleh = 0;
	delete = 0;
	line.offset.x = 0;
	line.offset.y = 0;
	offset.x = 0;
	line.color = 0xffffff;
	offset.y = 0;
	map_offset.x = 0;
	map_offset.y = 0;
	ctrl = 0;
	shift = 0;
	msbutton = 2;
	wind = init_wind(wind);
	mouse_pos.x = 0;
	mouse_pos.y = 0;
	fd = open("lines.txt", O_CREAT | O_RDWR | O_APPEND);
	if ((a = get_next_line(fd, &buf)) != -1 || a != 0)
	{
		flag = 1;
		walls = update_walls(walls, &w_coords, fd, flag);
		re_draw_walls(fd, wind, w_coords, walls, map_offset);
		if (select != -1)
			draw_select(fd, wind, w_coords[select], map_offset);
		close (fd);
		fd = open("lines.txt", O_RDWR | O_APPEND);
		ft_strdel(&buf);
	}
	close (fd);
	fd = open("lines.txt", O_CREAT | O_RDWR | O_APPEND);
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_KEYDOWN)
			{
				SDL_FillRect(wind.screen, NULL, 0x000000);
				draw_grid(wind, mouse_pos, offset, map_offset);
				re_draw_walls(fd, wind, w_coords, walls, map_offset);
				if (select != -1)
					draw_select(fd, wind, w_coords[select], map_offset);
				if (check_key_down(wind, &ctrl, &drawing, &shift, select, w_coords, walls) == 0)
				{
					close(fd);
					return (0);
				}
			}
			if (wind.event.type == SDL_MOUSEMOTION)
			{
				past_pos.x = mouse_pos.x;
				past_pos.y = mouse_pos.y;
				mouse_pos.x = wind.event.motion.x;
				mouse_pos.y = wind.event.motion.y;
				if (msbutton == 1 && ctrl == 1)
				{
					SDL_FillRect(wind.screen, NULL, 0x000000);
					offset.x -= mouse_pos.x - past_pos.x;
					offset.y -= mouse_pos.y - past_pos.y;
					map_offset.x += mouse_pos.x - past_pos.x;
					map_offset.y += mouse_pos.y - past_pos.y;
					draw_grid(wind, mouse_pos, offset, map_offset);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
					if (select != -1)
						draw_select(fd, wind, w_coords[select], map_offset);
					close (fd);
					fd = open("lines.txt", O_RDWR | O_APPEND);
				}
				if (msbutton == 1 && shift == 0 && select != -1)
				{
					SDL_FillRect(wind.screen, NULL, 0x000000);
					draw_grid(wind, mouse_pos, offset, map_offset);
					w_coords = move_line(walls, w_coords, mouse_pos, past_pos, &select, map_offset, fd, &delete);
					walls = update_walls(walls, &w_coords, fd, flag);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
					if (select != -1)
						draw_select(fd, wind, w_coords[select], map_offset);
				}
				if (drawing == 1)
				{
					SDL_FillRect(wind.screen, NULL, 0x000000);
					draw_grid(wind, mouse_pos, offset, map_offset);
					if (flag == 1)
					{
						walls = update_walls(walls, &w_coords, fd, flag);
						re_draw_walls(fd, wind, w_coords, walls, map_offset);
						if (select != -1)
							draw_select(fd, wind, w_coords[select], map_offset);
						close (fd);
						fd = open("lines.txt", O_RDWR | O_APPEND);
					}
				}
			}
			if (wind.event.type == SDL_MOUSEBUTTONDOWN)
			{
				select = check_select(shift, select, mouse_pos, walls, w_coords, map_offset);
				msbutton = 1;
				start_line = snap_line(walls, w_coords, mouse_pos, map_offset);
				if (ctrl == 1 || shift == 1 || select != -1)
					drawing = 0;
				else
					drawing = 1;
			}
			else if (wind.event.type == SDL_MOUSEBUTTONUP)
			{
				msbutton = 0;
				if (shift == 1)
				{
					walls = update_walls(walls, &w_coords, fd, flag);
					SDL_FillRect(wind.screen, NULL, 0x000000);
					draw_grid(wind, mouse_pos, offset, map_offset);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
					if (select != -1)
						draw_select(fd, wind, w_coords[select], map_offset);
					select = select_wall(mouse_pos, walls, w_coords, map_offset);
				}
				if (drawing == 1)
				{
					end_line = snap_line(walls, w_coords, mouse_pos, map_offset);
					write_l_coords(start_line, end_line, fd, map_offset);
					walls = update_walls(walls, &w_coords, fd, flag);
					SDL_FillRect(wind.screen, NULL, 0x000000);
					draw_grid(wind, mouse_pos, offset, map_offset);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
					if (select != -1)
						draw_select(fd, wind, w_coords[select], map_offset);
				}
				drawing = 0;
				flag = 1;
			}
			if (wind.event.type == SDL_KEYUP)
				check_key_up(wind, &ctrl, &drawing, &shift, &delete);
			if (drawing == 1)
			   ft_draw_line2(wind, start_line, mouse_pos, line);
		}
		if (bleh == 0 || bleh == 2)
		{
			bleh = 1;
			draw_grid(wind, mouse_pos, offset, map_offset);
			if (bleh == 2)
			{
				flag = 1;
				walls = update_walls(walls, &w_coords, fd, flag);
				re_draw_walls(fd, wind, w_coords, walls, map_offset);
				if (select != -1)
					draw_select(fd, wind, w_coords[select], map_offset);
				close (fd);
				fd = open("lines.txt", O_RDWR | O_APPEND);
			}
		}
		SDL_UpdateWindowSurface(wind.window);
	}
}
