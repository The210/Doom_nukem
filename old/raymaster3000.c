/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymaster3000.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 20:53:48 by smerelo           #+#    #+#             */
/*   Updated: 2018/11/11 21:38:35 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_cast(t_cast *cast, t_player player)
{
	cast->e = 0.000001;
	cast->x_pos = player.pos.x;
	cast->y_pos = player.pos.y;
	cast->i = (int)player.pos.x;
	cast->j = (int)player.pos.y;
	cast->x_step = player.ray.x > 0 ? 1 : -1;
	cast->y_step = player.ray.y > 0 ? 1 : -1;
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
	if (j < 0 || i < 0 || !(map[j][i]) || (map[j][i] >= 'A' && map[j][i] <= 'Z') || map[j][i] == '+' || map[j][i] == '1')
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

t_cast	vertical_ray(t_cast *cast, t_player player, char **map)
{
	cast->y_pos += floor(cast->y_pos) + (player.ray.y > 0) -
		(player.ray.y < 0) - cast->y_pos;
	cast->j += cast->y_step;
	while ((cast->object = collision(cast->i, cast->j, map)) == 0)
	{
		cast->y_pos += (player.ray.y > 0) - (player.ray.y < 0);
		cast->j += cast->y_step;
	}
	return (*cast);
}

t_cast	raycast(t_player player, char **map, t_cast *cast)
{
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
	return (*cast);
}

void		rays(t_player player, char **map, t_wall *w_coords, char **walltxt, t_wind wind, t_wall corners)
{
	int		i;
	int		height;
	t_wall	scorners;
	//t_cast	*cast;
	t_cast	second_cast;

	i = -(SCREEN_WIDTH / 2);
		while (++i < (SCREEN_WIDTH / 2))
		{
			height = -1;
			player.ray.x = player.dir.x + (player.plane.x * -i / (SCREEN_WIDTH / 2));
			player.ray.y = player.dir.y + (player.plane.y * -i / (SCREEN_WIDTH / 2));
			init_cast(&second_cast, player);
			while (height == -1)
			{
			//	printf("cast.i : %i  cast.j : %i\n", second_cast.i, second_cast.j);
				second_cast = raycast(player, map, &second_cast);
				height = (1 * (double)((double)SCREEN_WIDTH / (double) SCREEN_HEIGHT) * check_distance(player, second_cast, w_coords, map, walltxt, corners));
				//if (height != -1)
					printf("height: %i\n", height);
				second_cast.dx= player.ray.x > 0 ? floor(second_cast.x_pos) + 1 - second_cast.x_pos :
				ceil(second_cast.x_pos) - 1 - second_cast.x_pos;
				second_cast.dy = player.ray.y > 0 ? floor(second_cast.y_pos) + 1 - second_cast.y_pos :
				ceil(second_cast.y_pos) - 1 - second_cast.y_pos;
				move_ray(&second_cast, player);
				second_cast.object = 0;
			}
			draw_column(wind, height, i);
		}
		SDL_UpdateWindowSurface(wind.window);
}

/*int			main(int argc, char **argv)
{
	t_player	player;
	t_wind		wind;
	t_fd		fd;
	t_wall		*corners;
	t_wall		scorners;
	char		**map;
	double		tmp;
	char 		**walls;
	int			flag;
	double		temp;
	t_wall		*w_coords;

	flag = 0;
	walls = update_walls(walls, &w_coords, fd, flag);
	corners = find_corners(walls, w_coords, corners);
	scorners = *corners;
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
				if (wind.event.key.keysym.sym == SDLK_w)
				{
					player.pos.x  += player.dir.x * 0.09;
					player.pos.y += player.dir.y * 0.09;
				}
				if (wind.event.key.keysym.sym == SDLK_s)
				{
					player.pos.x -= player.dir.x * 0.09;
					player.pos.y -= player.dir.y * 0.09;
				}
				if (wind.event.key.keysym.sym == SDLK_d)
				{
					player.pos.x -= player.plane.x * 0.09;
					player.pos.y -= player.plane.y * 0.09;
				}
				if (wind.event.key.keysym.sym == SDLK_a)
				{
					player.pos.x += player.plane.x * 0.09;
					player.pos.y += player.plane.y * 0.09;
				}
				if (wind.event.key.keysym.sym == SDLK_RIGHT)
				{
					temp = player.dir.x;
					player.dir.x = player.dir.x * cos(0.07) + player.dir.y * (-sin(0.07));
					player.dir.y = temp * sin(0.07) + player.dir.y * cos(0.07);
				}
				SDL_FillRect(wind.screen, NULL, 0x000000);

			}
			//printf("pos.x: %f  pos.y: %f\n", player.pos.x, player.pos.y);
			rays(player, map, w_coords, walls, wind, scorners);
		}
	}
}*/
