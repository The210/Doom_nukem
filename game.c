/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:34:48 by smerelo           #+#    #+#             */
/*   Updated: 2018/12/06 19:34:53 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "doom.h"

int     main(int argc, char** argv)
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
    while(1)
    {
        while(SDL_PollEvent(&wind.event))
        {
            if (wind.event.type == SDL_KEYDOWN)
            {
				if (wind.event.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_DestroyWindow(wind.window);
					SDL_Quit();
					return (0);
				}
            }      
        }
    }
}