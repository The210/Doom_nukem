/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:23:19 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/08 22:02:31 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "libft.h"
# include "get_next_line.h"

# define SCREEN_HEIGHT 1000
# define SCREEN_WIDTH 1000
# define TEXTURE 500

typedef struct	s_pixels
{
	Uint32		*pixels;
	Uint32		pixel;
	Uint32		color;
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_pixel;

typedef	struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_cast
{
	double		x_pos;
	double		y_pos;
	int			object;
	int			i;
	int			j;
	int			x_step;
	int			y_step;
	double		dx;
	double		dy;
	double		slope;
	double		e;
	int			column;
}				t_cast;

typedef struct	s_misc
{
	int			x;
	int			y;
	int			height;
	int			texturecolumn;
	double		stepy;
	Uint32		color;
	int			side;
	int			orientation;
	double		scale;

}				t_misc;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_special
{
	t_vector	p1;
	t_vector	p2;
	t_vector	spawn;
	int			error;
}				t_special;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray;
	double		angularspeed;
	double		speed;
	double		runspeed;
	double		crouchspeed;
	double		thetal;
	double		thetar;
	double		wspeed;
	double		aspeed;
	double		sspeed;
	double		dspeed;
	int			error;
}				t_player;

typedef struct	s_wind
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_Surface	*used;
	SDL_Event	event;
}				t_wind;

typedef struct	s_texture
{
	SDL_Surface	*north;
	SDL_Surface	*south;
	SDL_Surface	*west;
	SDL_Surface	*east;
	SDL_Surface	*portal;
	SDL_Surface	*door;
}				t_texture;

#endif
