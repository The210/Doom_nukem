/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:23:19 by dhorvill          #+#    #+#             */
/*   Updated: 2018/10/08 22:28:26 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "libft.h"
# include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>

# define SCREEN_HEIGHT 1250
# define SCREEN_WIDTH 1250
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

typedef struct	s_fd
{
	int			walls;
	int			squares;
	int			map;
}				t_fd;

typedef	struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef	struct	s_line
{
	float		dx;
	int			sx;
	float		dy;
	int			sy;
	float		m;
	float		pb;
	int			intm;
	int			intb;
	int			color;
	t_coord		offset;
}				t_line;

typedef struct	s_wall
{
	t_coord		start;
	t_coord		end;
	int			error;
}				t_wall;

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

typedef struct	s_dvector
{
	t_vector	start;
	t_vector	end;
}				t_dvector;

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

void			put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32			get_pixel(SDL_Surface *surface, int x, int y);
t_line			mdy(t_wind wind, t_coord point, t_coord next_point, t_line line);
t_line			mdx(t_wind wind, t_coord point, t_coord next_point, t_line line);
int				ft_draw_line2(t_wind wind, t_coord point, t_coord next_point, t_line line);
void			draw_grid(t_wind wind, t_coord mouse_pos, t_coord offset, t_coord map_offset);
int				in_liner(t_coord start, t_coord end, t_vector temp_coords);
void			line_path(t_coord start, t_coord end, t_fd fd);
t_wall			find_croners(char **walls, t_wall *w_coords, t_wall corner);
char			**create_map(t_fd fd, char **wals, t_wall *w_coords, char **map, t_wall *corners);
int				ft_iatoi(char *wall, int index);
char			**flood_all(char **map, t_wall corners);
void			write_map(t_fd, char **map);
char			**readmap(char *argv);
t_player		init_player(t_player player);
t_wind			init_wind(t_wind wind);
double			check_distance(t_player player, t_cast cast, t_wall *w_coords, char **map, char **walltxt);
char			**update_walls(char **walls, t_wall **w_coords, t_fd fd, int flag);

#endif
