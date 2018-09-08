/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nuke.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:27:55 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/08 22:01:41 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "stdio.h"

int		check_key_down(t_wind wind)
{
	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(wind.window);
		SDL_Quit();
		return (0);
	}
	return (1);
}

t_wind		init_wind(t_wind wind)
{
	wind.screen = NULL;
	wind.window = SDL_CreateWindow("Doom_Nukem", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	wind.screen = SDL_GetWindowSurface(wind.window);
	return (wind);
}

int		main(int argc, char **argv)
{
	t_player	player;
	t_wind		wind;
	t_texture	texture;
	int			mousex;
	int			mousey;

	wind = init_wind(wind);
	mousex = 0;
	mousey = 0;
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_KEYDOWN)
				if (check_key_down(wind) == 0)
					return (0);
			if (wind.event.type == SDL_MOUSEMOTION)
			{
				mousex = wind.event.motion.x;
				mousey = wind.event.motion.y;
			}
		}
	}
}
