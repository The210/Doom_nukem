/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:53:02 by smerelo           #+#    #+#             */
/*   Updated: 2018/11/16 22:56:38 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wind		init_wind(t_wind wind)
{
	wind.screen = NULL;
	wind.window = SDL_CreateWindow("Doom_Nukem", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	wind.screen = SDL_GetWindowSurface(wind.window);
	return (wind);
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


int		check_keydown(t_wind wind)
{
	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(wind.window);
		SDL_Quit();
		return (0);
	}
	return (0);
}
/*int			main(int ac, char **av)
{
	t_tga specs;
	unsigned int *pixels;
	int i;
	int j;
	int iprime;
	int	jprime;
	double	size;
	unsigned int *res_img;
	t_wind wind;

	i = -1;
	size = 501;
	iprime = size - 1;
	wind = init_wind(wind);
	pixels = tga_load("download.tga", &specs);
	res_img = resize(pixels, specs, size);
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_KEYDOWN)
			{
				check_keydown(wind);
				return (0);
			}
			while (++i < size - 1)
			{
				j = -1;
				jprime = 0;
				while (++j < size - 1)
				{
					put_pixel32(wind.screen, j, i, (Uint32)res_img[iprime * (int)size + jprime] - 0xFF000000);
					jprime++;
				}
				iprime--;
			}
		}
		SDL_UpdateWindowSurface(wind.window);
	}

	return (0);
}*/

int			main(int argc, char **argv)
{
	t_tga specs;
	unsigned int *pixels;
	int i;
	int j;
	t_button button;
	int iprime;
	int jprime;
	double	size;
	unsigned int *res_img;
	t_wind wind;
	t_fd fd;

	i = -1;
	size = 501;
	iprime = size - 1;
	button.pos_x = 500;
	button.pos_y = 0;
	button.size = 500;
	button.name = "gravelle.tga";
	buttons(button, fd);
//	wind = init_wind(wind);
	/*pixels = tga_load("download.tga", &specs);
	res_img	= resize(pixels, specs, size);
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_KEYDOWN)
			{
				check_keydown(wind);
				return (0);
			}
			while (++i < size - 1)
			{
				j = -1;
				jprime = 0;
				while (++j < size - 1)
				{
					put_pixel32(wind.screen, j, i, (Uint32)res_img[iprime * (int)size + jprime] - 0xFF000000);
					jprime++;
				}
				iprime--;
			}
		}
		SDL_UpdateWindowSurface(wind.window);
	}*/
}




