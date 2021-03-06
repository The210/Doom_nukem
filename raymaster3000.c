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


t_wall		find_corners_game(char **walls, t_wall *w_coords)
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
	scorners.start.x /= SCREEN_WIDTH / 50;
	scorners.start.y /= SCREEN_HEIGHT / 50;
	scorners.end.x /= SCREEN_WIDTH / 50;
	scorners.end.y /= SCREEN_HEIGHT / 50;
	//corners = &scorners;
	return (scorners);
}

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

void		draw_column(t_wind wind, int height, int x, t_player player)
{
	int y;

	y = -1;
	while (++y < SCREEN_HEIGHT * 1.3)
	{
		//to optmize
			if (y < height)
			{
				if (y + (player.viewoff + player.posz * (double)((double)height/100)) + SCREEN_HEIGHT / 2 < SCREEN_HEIGHT)
					put_pixel32(wind.screen, x - SCREEN_WIDTH / 2, SCREEN_HEIGHT  / 2 + y + (player.viewoff + player.posz * (double)((double)height/100)), 0x0000FF);
				if(SCREEN_HEIGHT / 2 - y + (player.viewoff + player.posz * (double)((double)height/100)) >= 0)
					put_pixel32(wind.screen, x - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y + (player.viewoff + player.posz * (double)((double)height/100)), 0x0000FF);
			}
			else
			{
				if (y + (player.viewoff + player.posz * (double)((double)height/100)) + SCREEN_HEIGHT / 2 < SCREEN_HEIGHT)
					put_pixel32(wind.screen, x - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + y + (player.viewoff + player.posz * (double)((double)height/100)), 0x556a8c);
				if(SCREEN_HEIGHT / 2 - y + (player.viewoff + player.posz * (double)((double)height/100))>= 0)
					put_pixel32(wind.screen, x - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y + (player.viewoff + player.posz * (double)((double)height/100)), 0x556a8c);
			}
	}
}

int			collision(int i, int j, char **map)
{
	int map_len;
	int	map_height;

	map_len = ft_tablen(map);
	map_height = ft_strlen(map[0]);
	if (j < 0 || i < 0 || j >= map_len || i >= map_height || (map[j][i] >= 'A' && map[j][i] <= 'Z') || map[j][i] == '+' || map[j][i] == '1')
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

	i = -(SCREEN_WIDTH / 2) - 1;
		while (++i < (SCREEN_WIDTH / 2))
		{
			height = -1;
			player.ray.x = player.dir.x + (player.plane.x * -i / (SCREEN_WIDTH));
			player.ray.y = player.dir.y + (player.plane.y * -i / (SCREEN_WIDTH));
			init_cast(&second_cast, player);
			while (height == -1)
			{
				second_cast = raycast(player, map, &second_cast);
				height =  (1 * (double)((double)SCREEN_WIDTH / (double) SCREEN_HEIGHT) * (check_distance(player, second_cast, w_coords, map, walltxt, corners)));
				advance_one(player, map, &second_cast);
				second_cast.object = 0;
			}
			draw_column(wind, height, i, player);
		}
		//SDL_UpdateWindowSurface(wind.window);
}



/*int			main(int argc, char **argv)
{
	t_player	player;
	t_wind		wind;
	t_fd		fd;
	t_wall		corners;
	t_wall		scorners;
	char		**map;
	double		tmp;
	char 		**walls;
	int			flag;
	int			jump_height;
	double		temp;
	double 		crouch;
	t_wall		*w_coords;
	t_gwall		*gw_coords;
//	TTF_Font	*police;
	SDL_Color	black;
	SDL_Surface	*text;
	t_coord		past_pos;
	t_coord		mouse_pos;
	SDL_Rect	position;

	jump_height = 100;
	text = NULL;
	black.r = 255;
	crouch = -50;
	black.g = 255;
	black.b = 255;
	//police = NULL;
	flag = 0;
	walls = update_walls(walls, &w_coords, fd, flag);
	corners = find_corners_game(walls, w_coords);
	scorners = corners;
	gw_coords = createGameWalls(w_coords, walls, scorners);
	wind = init_wind(wind);
//	if(TTF_Init() == -1)
//{
//	printf("error\n");
//	return(0);
//}
	player = init_player(player);
	//police = TTF_OpenFont("font.ttf", 20);
	map = readmap(argv[1]);
	position.h = 50;
	position.w = 100;
	rays(player, map, w_coords, walls, wind, scorners);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_SetWindowGrab(wind.window, 1);

	SDL_UpdateWindowSurface(wind.window);
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_MOUSEMOTION)
			{
				SDL_GetRelativeMouseState(&mouse_pos.x, &mouse_pos.y);
				temp = player.dir.x;
				player.dir.x = player.dir.x * cos((double)((double)(-mouse_pos.x) / 500)) + player.dir.y * sin((double)(((double)(-mouse_pos.x)) / 500));
				player.dir.y = player.dir.y * cos((double)((double)(-mouse_pos.x) / 500)) - temp * sin((double)((double)((double)(-mouse_pos.x) / 500)));
				player.plane.x = player.dir.y;
				player.plane.y = -player.dir.x;
				if(player.viewoff + -mouse_pos.y + player.posz < 390 && player.viewoff + -mouse_pos.y + player.posz > -390)
					player.viewoff += -mouse_pos.y;
			}
			if (wind.event.type == SDL_KEYDOWN)
			{
				if (!(check_char_down(&player, wind)))
					return (0);
			}
			if (wind.event.type == SDL_KEYUP)
				reset_char(&player, wind);
		}
		player = jump_crouch(player);
		mod_char(&player, gw_coords, walls);
		SDL_FillRect(wind.screen, NULL, 0x000000);
		rays(player, map, w_coords, walls, wind, scorners);
		SDL_UpdateWindowSurface(wind.window);
	}
}*/
