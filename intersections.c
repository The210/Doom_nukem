/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 20:47:04 by dhorvill          #+#    #+#             */
/*   Updated: 2018/11/07 21:39:43 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <stdio.h>

t_vector	normalize(t_vector a)
  {
  	double d;

  	d = sqrt(pow(a.x, 2) + pow(a.y, 2));
 	 a.x /= d;
  	a.y /= d;
  	return (a);
  }
/*  double	dot_product(t_vector a, t_vector b)
  {
  t_vector	result;

  result.x = a.x * b.x;
  result.y = a.y * b.y;
  return (result.x + result.y);
  }

  t_vector	sub_vector(t_vector a, t_vector b)
  {
  t_vector result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  return (result);
  }

  t_vector	add_vector(t_vector a, t_vector b)
  {
  t_vector	result;

  result.x = a.x + b.x;
  result.y = a.y + b.y;
  return (result);
  } */

double		distance_calc(t_vector start, t_vector end)
{
	double	result;

	result = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
	return (result);
}

int			in_front(t_dvector ray, t_cast cast, t_vector result)
{
	t_vector dir;

	dir.x = result.x - ray.start.x > 0 ? 1 : -1;
	dir.y = result.y - ray.start.y > 0 ? 1 : -1;
	return ((cast.x_step == dir.x && cast.y_step == dir.y));
/*	if (cast.x_step != dir.x || cast.y_step != dir.y)
		return (0);
	else
		return (1);*/

}

/*int			in_segment(t_vector result, t_dvector ray)
{
	double		to_point;
	double		to_end;

	to_point = distance_calc(ray.start, result);
	to_end = distance_calc(ray.start, ray.end) + sqrt(2);
	//if (to_point <= to_end)
	//	printf("does segment\n");
	return (to_point <= to_end);
}*/

/*int			in_segment(t_vector result, t_cast cast)
{
	//printf("result.x: %f result.y: %f cast.i :%i cast.j %i\n", result.x, result.y, cast.i, cast.j);
	return (result.x <= cast.i + 1 && result.x >= cast.i - 1 && result.y <= cast.j + 1 && result.y >= cast.j - 1);
}*/

t_cast			advance_one(t_player player, char **map, t_cast *cast)
{
	if (!(fabs(player.ray.x) < cast->e))
		cast->slope = player.ray.y / player.ray.x;
	else
	{
		cast->y_pos += floor(cast->y_pos) + (player.ray.y > 0) -
		(player.ray.y < 0) - cast->y_pos;
		cast->j += cast->y_step;
		return (*cast);
	}
	cast->dx= player.ray.x > 0 ? floor(cast->x_pos) + 1 - cast->x_pos :
		ceil(cast->x_pos) - 1 - cast->x_pos;
	cast->dy = player.ray.y > 0 ? floor(cast->y_pos) + 1 - cast->y_pos :
		ceil(cast->y_pos) - 1 - cast->y_pos;
	move_ray(cast, player);
	return (*cast);
}

int				in_segment(t_vector result, t_cast cast, t_dvector ray)
{
	t_coord to_inter;
	t_coord	to_end;
	double	e;

	e = 0.000001;
	to_end.x = cast.x_pos - ray.start.x >= e ? 1 : -1;
	to_end.y = cast.y_pos - ray.start.y >= e ? 1 : -1;
	to_inter.x = result.x - ray.start.x >= e ? 1 : -1;
	to_inter.y = result.y - ray.start.y >= e ? 1 : -1;
	if (to_end.x != to_inter.x || to_end.y != to_inter.y)
		return (0);
	to_end.x = ray.start.x - cast.x_pos >= e ? 1 : -1;
	to_end.y = ray.start.y - cast.y_pos >= e ? 1 : -1;
	to_inter.x = result.x - cast.x_pos >= e ? 1 : -1;
	to_inter.y = result.y - cast.y_pos >= e ? 1 : -1;
	if (to_end.x != to_inter.x || to_end.y != to_inter.y)
		return (0);
	return (1);
}

int			in_wall(t_dvector wall, t_vector result)
{
	t_coord dir;
	t_coord r_pos;
	double	e;

	e = 0.000001;
	dir.x = wall.end.x - wall.start.x >= e ? 1 : -1;
	dir.y = wall.end.y - wall.start.y >= e ? 1 : -1;
	r_pos.x = result.x - wall.start.x >= e ? 1 : -1;
	r_pos.y = result.y - wall.start.y >= e ? 1 : -1;
	if (dir.x != r_pos.x || dir.y != r_pos.y)
		return (0);
	dir.x = wall.start.x - wall.end.x >= e ? 1 : -1;
	dir.y = wall.start.y - wall.end.y >= e ? 1 : -1;
	r_pos.x = result.x - wall.end.x >= e ? 1 : -1;
	r_pos.y = result.y - wall.end.y >= e ? 1 : -1;
	if (dir.x != r_pos.x || dir.y != r_pos.y)
		return (0);
	return (1);
}

int			intersects(t_dvector ray, t_dvector line)
{
	double m1;
	double m2;

	if (ray.start.x == ray.end.x) 
		return !(line.start.x == line.end.x && ray.start.x != line.start.x);
	else if (line.start.x == line.end.x) 
		return (1);
	else 
	{
		m1 = (ray.start.y - ray.end.y) / (ray.start.x - ray.end.x);
		m2 = (line.start.y - line.end.y) / (line.start.x - line.end.x);
		return (m1 != m2);
	}
}

t_vector	intersect_point(t_dvector ray, t_dvector wall, t_vector *med_result)
{
	t_vector	det;
	//x1 : ray.start.x  y1: ray.start.y
	//x2: ray.end.x y2: ray.end.y
	//x3: wall.start.x y3 wall.start.y
	//x4: wall.end.x y4: wall.start.y
	det.x = (((ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (wall.start.x - wall.end.x) - (ray.start.x - ray.end.x) * (wall.start.x * wall.end.y - wall.start.y * wall.end.x))
	/ ((ray.start.x - ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x - wall.end.x)));
	//*det.x = ((ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (wall.start.x - wall.end.x) - (ray.start.x - ray.end.x) * (wall.start.x * wall.end.y - wall.start.y * wall.end.x)) / 
	//((ray.start.x - ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x - wall.end.x));

	det.y = ((ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (wall.start.y - wall.end.y) - 
	(ray.start.y - ray.end.y) * (wall.start.x * wall.end.y - wall.start.y * wall.end.x)) / ((ray.start.x - ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x - wall.end.x));
	*med_result = det;
	return (det);
}

double		check_distance(t_player player, t_cast cast, t_wall *w_coords, char **map, char **walltxt, t_wall corners)
{
	t_dvector	walls;
	t_dvector	ray;
	t_cast		tmp_cast;
	t_vector	result;
	t_vector	med_result;
	t_vector	square;
	int			index;
	int			flag;
	t_vector	start;
	double		distance;
	double		shorter_distance;
	int map_height;
	int map_len;
	int	walltxtlen;
	int i;
	int j;
	int k;

	flag = 0;
	start.x = player.pos.x;
	start.y = player.pos.y;
	square.x = cast.x_pos;
	square.y = cast.y_pos;
	tmp_cast = cast;
	shorter_distance = -1;
	map_len = ft_tablen(map);
	map_height = ft_strlen(map[0]);
	walltxtlen = ft_tablen(walltxt);
	tmp_cast = advance_one(player, map, &tmp_cast);
	if (cast.j >= 0 && cast.i >= 0 && cast.j < map_len && cast.i < map_height)// && map[cast.j][cast.i] == '+')
	{
		index = -1;
		while (++index < walltxtlen)
		{
			walls.start.x = ((double)w_coords[index].start.x  / (double)(SCREEN_WIDTH / 50) - (double)corners.start.x);
			walls.start.y = ((double)w_coords[index].start.y  / (double)(SCREEN_HEIGHT / 50) - (double)corners.start.y);
			walls.end.x = ((double)w_coords[index].end.x / (double)(SCREEN_WIDTH / 50) - (double)corners.start.x);
			walls.end.y = ((double)w_coords[index].end.y / (double)(SCREEN_HEIGHT / 50) - (double)corners.start.y);
			ray.start.x = player.pos.x;
			ray.start.y = player.pos.y;
			ray.end.x = cast.x_pos;
			ray.end.y = cast.y_pos;
			med_result = intersect_point(ray, walls, &med_result);
			if (in_segment(med_result, tmp_cast, ray) && in_wall(walls, med_result))
			{
				distance = distance_calc(start, med_result);
				if (flag == 0)
				{
					flag = 1;
					shorter_distance = distance;
					result = med_result;
				}
				result = distance < shorter_distance ? med_result : result;
				shorter_distance = distance < shorter_distance ? distance : shorter_distance;
			}
		}
	}
	else if (cast.j >= 0 && cast.i >= 0 && cast.j < map_len && cast.i < map_height && map[cast.j][cast.i] >= 'A' && map[cast.j][cast.i] <= 'Z')
	{
		index = map[cast.j][cast.i] - 65;
		while (index < ft_tablen(walltxt))
		{
			if ((index % 26) == (map[cast.j][cast.i] - 65))
			{
				walls.start.x = ((double)w_coords[index].start.x / (double)(SCREEN_WIDTH / 50) - (double)corners.start.x) ;
				walls.start.y = ((double)w_coords[index].start.y / (double)(SCREEN_HEIGHT / 50) - (double)corners.start.y) ;
				walls.end.x = ((double)w_coords[index].end.x / (double)(SCREEN_WIDTH / 50) - (double)corners.start.x) ;
				walls.end.y = ((double)w_coords[index].end.y  / (double)(SCREEN_HEIGHT / 50) - (double)corners.start.y);
				ray.start.x = player.pos.x;
				ray.start.y = player.pos.y;
				ray.end.x = cast.x_pos; //possible error
				ray.end.y = cast.y_pos; // possible error
				med_result = intersect_point(ray, walls, &med_result);
				if (in_wall(walls, med_result) && in_segment(med_result, tmp_cast, ray))
				{
					distance = distance_calc(start, med_result);
					if (flag == 0)
					{
						flag = 1;
						shorter_distance = distance;
						result = med_result;
					}
					result = distance < shorter_distance ? med_result : result;
					shorter_distance = distance < shorter_distance ? distance : shorter_distance;
				}
			}
			index++;
		}
	}
	else if (cast.j < 0 || cast.i < 0 || cast.j >= map_len || cast.i >= map_height)
		return (SCREEN_HEIGHT / (fabs(player.dir.x * (cast.x_pos - player.pos.x) + player.dir.y * (cast.y_pos - player.pos.y))));
	else
		return (-1);
	if (flag == 0)
		return (-1);
	//printf("cast.j :%i cast.i: %i\n", cast.j, cast.i);
	//printf("map thing : %c\n", map[cast.j][cast.i]);
	//printf("shorter_distance: %f\n", shorter_distance);
//if (shorter_distance <= (distance_calc(start, square)) + 2 && shorter_distance != -1)
	return (SCREEN_HEIGHT / (fabs(player.dir.x * (result.x - player.pos.x) + player.dir.y * (result.y - player.pos.y))));
/*else
{
	return (-1);
}*/
	//	printf("shorter_distance: %f\n", shorter_distance);
		//return (shorter_distance);
}

/*int		main(void)
{
	t_dvector	line1;
	t_dvector	line2;
	t_vector	det;
	line1.start.x = -15.16;
	line1.end.x = -6.58;
	line1.start.y = -6.07;
	line1.end.y = 0.53;
	line2.start.x = -11.2;
	line2.end.x = -1.22;
	line2.start.y = 6.63;
	line2.end.y = 5.71;
	det = intersect_point(line1, line2);
	printf("x:%f y:%f", det.x, det.y);
	return (0);
}*/