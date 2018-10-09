/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 20:47:04 by dhorvill          #+#    #+#             */
/*   Updated: 2018/10/08 22:35:09 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*t_vector	normalize(t_vector a)
  {
  double d;

  d = sqrt(pow(a.x, 2) + pow(a.y, 2));
  a.x /= d;
  a.y /= d;
  return (a);
  }
  double	dot_product(t_vector a, t_vector b)
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
  }*/

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

t_vector	intersect_point(t_dvector ray, t_dvector wall)
{
	t_vector	det;

	det.x = ((ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (wall.start.x - wall.end.x) - (ray.start.x - ray.end.x) * (wall.start.x * wall.end.y - wall.start.y * wall.end.x)) / ((ray.start.x - ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x - wall.end.x));

	det.y = ((ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x * wall.end.y - wall.start.y * wall.end.x)) / ((ray.start.x - ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x - wall.end.x));
	return (det);
}

double		distance_calc(t_vector start, t_vector end)
{
	double	result;

	result = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
	return (result);
}

double		check_distance(t_player player, t_cast cast, t_wall *w_coords, char **map, char **walltxt)
{
	t_dvector	walls;
	t_dvector	ray;
	t_vector	result;
	t_vector	square;
	int			index;
	int			flag;
	t_vector	start;
	double		distance;
	double		shorter_distance;

	flag = 0;
	
	start.x = player.pos.x;
	start.y = player.pos.y;
	square.x = cast.x_pos;
	square.y = cast.y_pos;
	if (map[cast.j][cast.i] == '+')
	{
		index = -1;
		while (++index < ft_tablen(walltxt))
		{
			walls.start.x = w_coords[index].start.x;
			walls.start.y = w_coords[index].start.y;
			walls.end.x = w_coords[index].end.x;
			walls.end.y = w_coords[index].end.y;
			ray.start.x = player.pos.x;
			ray.start.y = player.pos.y;
			ray.end.x = player.ray.x;
			ray.end.y = player.ray.y;
			if (intersects(ray, walls))
			{
				result = intersect_point(ray, walls);
				distance = distance_calc(start, result);
				if (flag == 0)
				{
					flag = 1;
					shorter_distance = distance;
				}
				shorter_distance = distance < shorter_distance ? distance : shorter_distance;
			}
		}
	}
	else if (map[cast.j][cast.i] >= 'A' && map[cast.j][cast.i] <= 'Z')
	{
		index = map[cast.j][cast.i] - 65;
		while (++index < ft_tablen(walltxt))
		{
			if (index % (map[cast.j][cast.i] - 65) == 0)
			{
				walls.start.x = w_coords[index].start.x;
				walls.start.y = w_coords[index].start.y;
				walls.end.x = w_coords[index].end.x;
				walls.end.y = w_coords[index].end.y;
				ray.start.x = player.pos.x;
				ray.start.y = player.pos.y;
				ray.end.x = player.ray.x;
				ray.end.y = player.ray.y;
				if (intersects(ray, walls))
				{
					result = intersect_point(ray, walls);
					distance = distance_calc(start, result);
				if (flag == 0)
				{
					flag = 1;
					shorter_distance = distance;
				}
				shorter_distance = distance < shorter_distance ? distance : shorter_distance;
				}
			}
		}
	}
	if (shorter_distance <= (distance_calc(start, square)) + sqrt(2))
		return (SCREEN_HEIGHT / (fabs(player.dir.x * (result.x - player.pos.x) + player.dir.y * (result.y - player.pos.y))));
	else
		return (-1);
}
