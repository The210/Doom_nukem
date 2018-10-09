/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymaster3000.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 20:53:48 by smerelo           #+#    #+#             */
/*   Updated: 2018/10/09 19:09:17 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_cast		*init_cast(t_cast *cast, t_player player)
{
	cast->x_pos = player.pos.x;
	cast->y_pos = player.pos.y;
	cast->i = (int)player.pos.x;
	cast->j = (int)player.pos.y;
	cast->e = 0.000001;
	cast->x_step = player.ray.x > 0 ? 1 : -1;
	cast->y_step = player.ray.y > 0 ? 1 : -1;
	return (cast);
}

void		draw_column(t_wind wind, int height, int x)
{
	int y;

	y = -1;
	while (++y < SCREEN_HEIGHT / 2)
	{
		if (y < height)
		{
			put_pixel32(wind.screen, x - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + y, 0x0000FF);
			put_pixel32(wind.screen, x - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y, 0x0000FF);
		}
		else
		{
			put_pixel32(wind.screen, x - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y, 0x000099);
			put_pixel32(wind.screen, x - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + y, 0x000099);
		}
	}
}

int			collision(int i, int j, char **map)
{
	if ((map[j][i] >= 'A' && map[j][i] <= 'Z') || map[j][i] == '+')
		return (1);
	else
		return (0);
}

void		move_ray(t_cast * cast, t_player player)
{
	if (fabs(cast->dy / cast->dx) < fabs(cast->slope))
	{
		cast->x_pos = cast->x_pos + cast->dy / cast->slope;
		cast->y_pos = cast->y_pos + cast->dy;
		cast->j += cast->y_step;
	}
	else if (fabs(cast->dy / cast->dx) == fabs(cast->slope))
	{
		cast->x_pos += cast->dx;
		cast->y_pos += cast->dy;
		cast->i += cast->x_step;
		cast->j += cast->y_step;
	}
	else
	{
		cast->x_pos = cast->x_pos + cast->dx;
		cast->y_pos = cast->y_pos + cast->slope * cast->dx;
		cast->i += cast->x_step;
	}
}

int		vertical_ray(t_cast *cast, t_player player, char **map)
{
	cast->y_pos += floor(cast->y_pos) + (player.ray.y > 0) -
		(player.ray.y < 0) - cast->y_pos;
	cast->j += cast->y_step;
	while ((cast->object = collision(cast->i, cast->j, map)) == 0)
	{
		cast->y_pos += (player.ray.y > 0) - (player.ray.y < 0);
		cast->j += cast->y_step;
	}
	return (cast->object);
}

int			raycast(t_player player, char **map, t_cast *cast)
{
	cast = init_cast(cast, player);
	if (!(fabs(player.ray.x) < cast->e))
		cast->slope = player.ray.y / player.ray.x;
	else
		return (vertical_ray(cast, player, map));
	while ((cast->object = collision(cast->i, cast->j, map)) == 0)
	{
		cast->dx= player.ray.x > 0 ? floor(cast->x_pos) + 1 - cast->x_pos :
			ceil(cast->x_pos) - 1 - cast->x_pos;
		cast->dy = player.ray.y > 0 ? floor(cast->y_pos) + 1 - cast->y_pos :
			ceil(cast->y_pos) - 1 - cast->y_pos;
		move_ray(cast, player);
	}
	return (cast->object);
}

void		rays(t_player player, char **map, t_wall *w_coords, char **walltxt, t_wind wind)
{
	int		i;
	int		height;
	t_cast	*cast;

	i = -(SCREEN_WIDTH / 2);
		while (++i < SCREEN_WIDTH / 2)
		{
			player.ray.x = player.dir.x + (player.plane.x * -i / (SCREEN_WIDTH / 2));
			player.ray.y = player.dir.y + (player.plane.y * -i / (SCREEN_WIDTH / 2));
			raycast(player, map, cast);
			height = (0.25 * ((double)SCREEN_WIDTH / (double) SCREEN_HEIGHT) * check_distance(player, *cast, w_coords, map, walltxt));
			draw_column(wind, height, i);
		}
}

int			main(int argc, char **argv)
{
	t_player	player;
	t_wind		wind;
	t_cast		cast;
	t_fd		fd;
	char		**map;
	char 		**walls;
	int			flag;
	t_wall		*w_coords;

	flag = 0;
	walls = update_walls(walls, &w_coords, fd, flag);
	wind = init_wind(wind);
	player = init_player(player);
	map = readmap(argv[1]);
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type== SDL_KEYDOWN)
			{
				if (wind.event.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_DestroyWindow(wind.window);
					SDL_Quit();
					return (0);
				}
			}
			rays(player, map, w_coords, walls, wind);
		}
	}
}
