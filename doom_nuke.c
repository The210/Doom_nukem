/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nuke.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:27:55 by dhorvill          #+#    #+#             */
/*   Updated: 2018/12/04 01:05:07 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"

void	check_key_up(t_wind wind, int *ctrl, int *drawing, int *shift, int *delete, int *snap)
{
	if (wind.event.key.keysym.sym == SDLK_LCTRL)
		*ctrl = 0;
	if (wind.event.key.keysym.sym == SDLK_LSHIFT)
		*shift = 0;
	if (wind.event.key.keysym.sym == SDLK_p)
		*delete = 1;
	if (wind.event.key.keysym.sym == SDLK_n)
		*snap = 1;
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

char		**read_lines(t_fd fd)
{
	char	*buf;
	int		ret;
	char	**walls;
	char	*str;

	str = ft_strnew(1);
	close(fd.walls);
	fd.walls = open("walls.txt", O_RDONLY);
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
	/*
	if (str)
		ft_strdel(&str); */
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

void		re_draw_walls(t_fd fd, t_wind wind, t_wall *w_coords, char **walls, t_coord map_offset)
{
	int		i;
	t_line	line;

	i = -1;
	line.offset = map_offset;
	line.color = 0xffffff;
	while (++i < ft_tablen(walls))
		ft_draw_line2(wind, w_coords[i].start, w_coords[i].end, line);
}

void		draw_select(t_fd fd, t_wind wind, t_wall w_coords, t_coord map_offset)
{
	t_line line;

	line.color = 0xffff00;
	line.offset = map_offset;
	ft_draw_line2(wind, w_coords.start, w_coords.end, line);
}

char		**update_walls(char **walls, t_wall **w_coords, t_fd fd, int flag)
{
	walls = read_lines(fd);
	/* if (*w_coords)
		free(*w_coords); */
	*w_coords = separate_walls(walls);
	return (walls);
}

void		write_l_coords(t_coord start, t_coord end, t_fd fd, t_coord offset)
{
	t_coord ln_start;
	t_coord ln_end;

	ln_start.x = start.x - offset.x;
	ln_start.y = start.y - offset.y;
	ln_end.x = end.x - offset.x;
	ln_end.y = end.y - offset.y;
	double length;
	length = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y , 2));
	if (length < 4000 && length > 8)
	{
		ft_putnbr_fd(start.x - offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(start.y - offset.y, fd.walls);
		ft_putchar_fd(':', fd.walls);
		ft_putnbr_fd(end.x - offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(end.y - offset.y, fd.walls);
		ft_putchar_fd('\n', fd.walls);
		line_path(ln_start, ln_end, fd);
	}
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
	if (dir.x != r_pos.x && dir.y != r_pos.y)
		return (0);
	dir.x = w_coord.start.x - w_coord.end.x > 0 ? 1 : -1;
	dir.y = w_coord.start.y - w_coord.end.y > 0 ? 1 : -1;
	r_pos.x = true_pos.x - w_coord.end.x > 0 ? 1 : -1;
	r_pos.y = true_pos.y - w_coord.end.y > 0 ? 1 : -1;
	if (dir.x != r_pos.x && dir.y != r_pos.y)
		return (0);
	return (1);

}

t_coord		snap_line_select(char **walls, t_wall *w_coords, t_coord mouse_pos, t_coord map_offset, int *select)
{
	int		i;
	double		scalar;
	int		distance;
	int		d;
	t_coord	start_line;
	t_vector	to_mouse;
	t_vector	wall;

	i = -1;
	start_line.x = mouse_pos.x;
	start_line.y = mouse_pos.y;

	if (walls)
	{
		while (++i < ft_tablen(walls))
		{
			if (i != *select)
			{
				distance = (abs((w_coords[i].end.y - w_coords[i].start.y) * (mouse_pos.x - map_offset.x) - (w_coords[i].end.x - w_coords[i].start.x) * (mouse_pos.y - map_offset.y) + (w_coords[i].end.x * w_coords[i].start.y) - (w_coords[i].end.y * w_coords[i].start.x)) / (sqrt(pow(w_coords[i].end.y - w_coords[i].start.y, 2) + pow(w_coords[i].end.x - w_coords[i].start.x, 2))));
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
				if (distance < 10 && in_line(mouse_pos, map_offset, w_coords[i]))
				{
					to_mouse.x = (w_coords[i].start.x - start_line.x);
					to_mouse.y = (w_coords[i].start.y - start_line.y);
					wall.x = (w_coords[i].end.x - w_coords[i].start.x);
					wall.y = (w_coords[i].end.y - w_coords[i].start.y);
					scalar = (to_mouse.x * wall.x) + (to_mouse.y * wall.y);
					d = sqrt(pow(wall.x, 2) + pow(wall.y, 2));
					start_line.x = (w_coords[i].start.x - ((int)(((scalar) / (pow(d, 2))) * wall.x)));
					start_line.y = (w_coords[i].start.y - ((int)(((scalar) / (pow(d, 2))) * wall.y)));
					break ;
				}
			}
		}
	}
	return (start_line);
}

t_coord		snap_line(char **walls, t_wall *w_coords, t_coord mouse_pos, t_coord map_offset)
{
	int		i;
	double		scalar;
	int		distance;
	int		d;
	t_coord	start_line;
	t_vector	to_mouse;
	t_vector	wall;

	i = -1;
	start_line.x = mouse_pos.x;
	start_line.y = mouse_pos.y;

	if (walls)
	{
		while (++i < ft_tablen(walls))
		{
			distance = (abs((w_coords[i].end.y - w_coords[i].start.y) * (mouse_pos.x - map_offset.x) - (w_coords[i].end.x - w_coords[i].start.x) * (mouse_pos.y - map_offset.y) + (w_coords[i].end.x * w_coords[i].start.y) - (w_coords[i].end.y * w_coords[i].start.x)) / (sqrt(pow(w_coords[i].end.y - w_coords[i].start.y, 2) + pow(w_coords[i].end.x - w_coords[i].start.x, 2))));
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
			if (distance < 10 && in_line(mouse_pos, map_offset, w_coords[i]))
			{
				to_mouse.x = (w_coords[i].start.x - (start_line.x - map_offset.x));
				to_mouse.y = (w_coords[i].start.y - (start_line.y - map_offset.y));
				wall.x = (w_coords[i].end.x - w_coords[i].start.x);
				wall.y = (w_coords[i].end.y - w_coords[i].start.y);
				scalar = (to_mouse.x * wall.x) + (to_mouse.y * wall.y);
				d = sqrt(pow(wall.x, 2) + pow(wall.y, 2));
				start_line.x = (w_coords[i].start.x - ((int)(((scalar) / (pow(d, 2))) * wall.x)) + map_offset.x);
				start_line.y = (w_coords[i].start.y - ((int)(((scalar) / (pow(d, 2))) * wall.y)) + map_offset.y);
				break ;
			}
		}
	}
	return (start_line);
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

void		change_squares(t_fd fd, t_wall *w_coords, char **walls)
{
	int i;

	close(fd.squares);
	fd.squares = open("squares.txt", O_RDWR | O_APPEND);
	truncate ("squares.txt", 0);
	close(fd.squares);
	fd.squares = open("squares.txt", O_RDWR | O_APPEND);
	i = -1;
	while (++i < ft_tablen(walls))
		line_path(w_coords[i].start, w_coords[i].end, fd);
}

void		change_fd(t_fd fd, t_wall *w_coords, char **walls, int *select, int *delete)
{
	int i;

	close(fd.walls);
	fd.walls = open("walls.txt", O_RDWR | O_APPEND);
	truncate("walls.txt", 0);
	close(fd.walls);
	fd.walls = open("walls.txt", O_RDWR | O_APPEND);
	i = -1;
	while (++i < ft_tablen(walls))
	{
		if (!(*delete == 1 && i == *select))
		{
			ft_putnbr_fd(w_coords[i].start.x, fd.walls);
			ft_putchar_fd('.', fd.walls);
			ft_putnbr_fd(w_coords[i].start.y, fd.walls);
			ft_putchar_fd(':', fd.walls);
			ft_putnbr_fd(w_coords[i].end.x, fd.walls);
			ft_putchar_fd('.', fd.walls);
			ft_putnbr_fd(w_coords[i].end.y, fd.walls);
			ft_putchar_fd('\n', fd.walls);
		}
		if (*delete == 1 && i == *select)
		{
			*select = -1;
			*delete = 0;
		}
	}
}

t_wall		*snap_all(char **walls, t_wall *w_coords, t_fd fd)
{
	int i;
	int p;
	int delete;
	t_coord zero;

	i = -1;
	p = -1;
	delete = 0;
	zero.x = 0;
	zero.y = 0;
	while (++i < ft_tablen(walls))
	{
		w_coords[i].start = snap_line_select(walls, w_coords, w_coords[i].start, zero, &i);
		w_coords[i].end = snap_line_select(walls, w_coords, w_coords[i].end, zero, &i);
	}
	change_fd(fd, w_coords, walls, &p, &delete);
	return (w_coords);
}

t_wall		*move_line(char **walls, t_wall *w_coords, t_coord mouse_pos, t_coord past_pos, int *select, t_coord map_offset, t_fd fd, int *delete)
{
	t_coord movement;
	t_coord zero;
	zero.x = 0;
	zero.y = 0;
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
	w_coords[*select].start = snap_line_select(walls, w_coords, w_coords[*select].start, zero, select);
	w_coords[*select].end = snap_line_select(walls, w_coords, w_coords[*select].end, zero, select);
	change_fd(fd, w_coords, walls, select, delete);
	return (w_coords);
}

/*int			main(int argc, char **argv)
{
	unsigned int *res_img;
	int			c_button;
	int			p_button;
	t_tga		specs;
	t_player	player;
	t_wind		wind;
	t_line		line;
	t_texture	texture;
	int			c;
	int			i;
	int			j;
	int			jprime;
	int			iprime;
	char		**walls;
	t_wall		*w_coords;
	t_coord		mouse_pos;
	t_coord		offset;
	t_coord		map_offset;
	int			select;
	t_coord		past_pos;
	t_fd		fd;
	int			flag;
	char		*buf;
	int			bleh;
	int			ctrl;
	int			a;
	int			drawing;
	int			snap;
	char		**map;
	int			shift;
	struct stat st = {0};
	int			msbutton;
	double		size;
	int			delete;
	t_coord		start_line;
	t_coord		end_line;
	t_wall		corners;
	int			rect;
	unsigned int *img;
	t_button	*buttons;
	t_wall		rect_pos;
	drawing = 0;
	c_button = 0;
	size = 500;
	rect = 0;
	flag = 0;
	snap = 0;
	select = -1;
	bleh = 0;
	delete = 0;
	line.offset.x = 0;
	line.offset.y = 0;
	offset.x = 0;
	offset.y = 0;
	line.color = 0xffffff;
	map_offset.x = 0;
	map_offset.y = 0;
	ctrl = 0;
	i = -1;
	iprime = 500 - 1;
	shift = 0;
	msbutton = 2;
	wind = init_wind(wind);
	mouse_pos.x = 0;
	mouse_pos.y = 0;
	c = -1;
	buttons = fill_all(fd);
	while (++c < buttons[0].len)
		buttons[c].select = 0;
//	img = tga_load("download.tga", &specs);
//	res_img	= resize(img, specs, 500);
	fd.map = open("map.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	fd.walls = open("walls.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	i = 0;
	//re_draw_walls(fd, wind, w_coords, walls, map_offset);
	if ((a = get_next_line(fd.walls, &buf)) != -1 || a != 0)
	{
		flag = 1;
		walls = update_walls(walls, &w_coords, fd, flag);
		draw_grid(wind, offset);
		re_draw_walls(fd, wind, w_coords, walls, map_offset);
		if (select != -1)
			draw_select(fd, wind, w_coords[select], map_offset);
		display_buttons(buttons, wind);
		close (fd.walls);
		fd.walls = open("walls.txt", O_RDWR | O_APPEND);
		//ft_strdel(&buf);
	}
	close (fd.walls);
	fd.walls = open("walls.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	fd.squares = open("squares.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_KEYDOWN)
			{
				SDL_FillRect(wind.screen, NULL, 0x000000);
				draw_grid(wind, offset);
				walls = update_walls(walls, &w_coords, fd, flag);
				re_draw_walls(fd, wind, w_coords, walls, map_offset);
				if (select != -1)
					draw_select(fd, wind, w_coords[select], map_offset);
				if (check_key_down(wind, &ctrl, &drawing, &shift, select, w_coords, walls) == 0)
				{
					//rwrite_edges(&corners, fd);
				//	if (map)
				//		ft_strdel(map);
					//map = create_map(fd, walls, w_coords, map, &corners);
					//map = flood_all(map, corners);
					//write_map(fd, map);
					close(fd.walls);
					close(fd.buttonss);
					free(buttons);
					return (0);
				}
			}
			if (wind.event.type == SDL_MOUSEMOTION)
			{
				past_pos.x = mouse_pos.x;
				past_pos.y = mouse_pos.y;
				mouse_pos.x = wind.event.motion.x;
				mouse_pos.y = wind.event.motion.y;
				if (rect == 1 && msbutton == 1 && ctrl == 0 && shift == 0)
				{
					SDL_FillRect(wind.screen, NULL, 0x000000);
					draw_grid(wind, offset);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
					display_buttons(buttons, wind);
					rect_pos.end = mouse_pos;
					draw_rect(wind, rect_pos);
				}
				if (msbutton == 1 && ctrl == 1)
				{
					SDL_FillRect(wind.screen, NULL, 0x000000);
					offset.x -= mouse_pos.x - past_pos.x;
					offset.y -= mouse_pos.y - past_pos.y;
					map_offset.x += mouse_pos.x - past_pos.x;
					map_offset.y += mouse_pos.y - past_pos.y;
					draw_grid(wind, offset);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
					if (select != -1)
						draw_select(fd, wind, w_coords[select], map_offset);
					close (fd.walls);
					fd.walls = open("walls.txt", O_RDWR | O_APPEND);
				}
				if (msbutton == 1 && shift == 0 && select != -1)
				{
					SDL_FillRect(wind.screen, NULL, 0x000000);
					draw_grid(wind, offset);
					w_coords = move_line(walls, w_coords, mouse_pos, past_pos, &select, map_offset, fd, &delete);
					walls = update_walls(walls, &w_coords, fd, flag);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
					if (select != -1)
						draw_select(fd, wind, w_coords[select], map_offset);
				}
				if (drawing == 1)
				{

					walls = update_walls(walls, &w_coords, fd, flag);
					SDL_FillRect(wind.screen, NULL, 0x000000);
					draw_grid(wind, offset);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
					display_buttons(buttons, wind);
					if (flag == 1)
					{
						walls = update_walls(walls, &w_coords, fd, flag);
						re_draw_walls(fd, wind, w_coords, walls, map_offset);
						if (select != -1)
							draw_select(fd, wind, w_coords[select], map_offset);
						close (fd.walls);
						fd.walls = open("walls.txt", O_RDWR | O_APPEND);
					}
				}
			}
			if (wind.event.type == SDL_MOUSEBUTTONDOWN)
			{
				if ((p_button = in_button_d(mouse_pos, buttons)) == -1)
				{
				if (rect == 1 && ctrl == 0 && shift == 0)
					{
						rect_pos.end = mouse_pos;
						rect_pos.start = mouse_pos;
					}
					select = check_select(shift, select, mouse_pos, walls, w_coords, map_offset);
					msbutton = 1;
					start_line = snap_line(walls, w_coords, mouse_pos, map_offset);
					if (ctrl == 1 || shift == 1 || select != -1 || rect == 1)
						drawing = 0;
					else
						drawing = 1;
				}
			}
			else if (wind.event.type == SDL_MOUSEBUTTONUP)
			{
				msbutton = 0;
				if (p_button != -1)
				{
					c = -1;
					c_button = in_button_u(mouse_pos, buttons, p_button, c_button);
					while (++c < buttons[0].len)
						buttons[c].select = 0;
					buttons[c_button].select = 1;
					printf("Current_button: %i\n", c_button);
					if (buttons[1].select == 1)
					{
						rect = 1;
					}
					else
						rect = 0;
					walls = update_walls(walls, &w_coords, fd, flag);
					SDL_FillRect(wind.screen, NULL, 0x000000);
					draw_grid(wind, offset);
					re_draw_walls(fd, wind, w_coords, walls, map_offset);
				}
				else
				{
					if (shift == 1)
					{
						walls = update_walls(walls, &w_coords, fd, flag);
						SDL_FillRect(wind.screen, NULL, 0x000000);
						draw_grid(wind, offset);
						re_draw_walls(fd, wind, w_coords, walls, map_offset);
						if (select != -1)
							draw_select(fd, wind, w_coords[select], map_offset);
						select = select_wall(mouse_pos, walls, w_coords, map_offset);
					}
					if (rect == 1)
					{
						write_rect(rect_pos, map_offset, fd);
						walls = update_walls(walls, &w_coords, fd, flag);
						SDL_FillRect(wind.screen, NULL, 0x000000);
						draw_grid(wind, offset);
						re_draw_walls(fd, wind, w_coords, walls, map_offset);
					}
					if (drawing == 1)
					{
						end_line = snap_line(walls, w_coords, mouse_pos, map_offset);
						write_l_coords(start_line, end_line, fd, map_offset);
						walls = update_walls(walls, &w_coords, fd, flag);
						SDL_FillRect(wind.screen, NULL, 0x000000);
						draw_grid(wind, offset);
						re_draw_walls(fd, wind, w_coords, walls, map_offset);
						if (select != -1)
							draw_select(fd, wind, w_coords[select], map_offset);
					}
					change_squares(fd, w_coords, walls);
					drawing = 0;
					flag = 1;
					if (map)
						ft_strdel(map);
					map = create_map(fd, walls, w_coords, map, &corners);
					map = flood_all(map, corners);
					write_map(fd, map);
				}
			}
			display_buttons(buttons, wind);
			if (wind.event.type == SDL_KEYUP)
				check_key_up(wind, &ctrl, &drawing, &shift, &delete, &snap);
			if (snap == 1 && ctrl == 0 && msbutton == 0 && shift == 0)
			{
				w_coords = snap_all(walls, w_coords, fd);
				walls = update_walls(walls, &w_coords, fd, flag);
				SDL_FillRect(wind.screen, NULL, 0x000000);
				draw_grid(wind, offset);
				re_draw_walls(fd, wind, w_coords, walls, map_offset);
				if (select != -1)
					draw_select(fd, wind, w_coords[select], map_offset);
				snap = 0;
			}
			snap = 0;
			if (drawing == 1)
				ft_draw_line2(wind, start_line, mouse_pos, line);
		}
		if (bleh == 0 || bleh == 2)
		{
			bleh = 1;
			if (bleh == 2)
			{
				flag = 1;
				walls = update_walls(walls, &w_coords, fd, flag);
				re_draw_walls(fd, wind, w_coords, walls, map_offset);
				if (select != -1)
					draw_select(fd, wind, w_coords[select], map_offset);
				close (fd.walls);
				fd.walls = open("walls.txt", O_RDWR | O_APPEND);
			}
		}
		SDL_UpdateWindowSurface(wind.window);
	}
}*/
