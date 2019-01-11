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
	return (!(cast.x_step != dir.x || cast.y_step != dir.y));
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

int			in_segment(t_vector result, t_cast cast)
{
	//printf("result.x: %f result.y: %f cast.i :%i cast.j %i\n", result.x, result.y, cast.i, cast.j);
	return (result.x >= cast.i && result.x <= cast.i + 1 && result.y >= cast.j && result.y <= cast.j + 1);
}

int			in_wall(t_dvector wall, t_vector result)
{
	t_vector dir;
	t_vector r_pos;

	dir.x = wall.end.x - wall.start.x > 0 ? 1 : -1;
	dir.y = wall.end.y - wall.start.y > 0 ? 1 : -1;
	r_pos.x = result.x - wall.start.x > 0 ? 1 : -1;
	r_pos.y = result.y - wall.start.y > 0 ? 1 : -1;
	if (dir.x != r_pos.x || dir.y != r_pos.y)
		return (0);
	dir.x = wall.start.x - wall.end.x > 0 ? 1 : -1;
	dir.y = wall.start.y - wall.end.y > 0 ? 1 : -1;
	r_pos.x = result.x - wall.end.x > 0 ? 1 : -1;
	r_pos.y = result.y - wall.end.y > 0 ? 1 : -1;
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

t_vector	intersect_point(t_dvector ray, t_dvector wall)
{
	t_vector	det;

	det.x = ((ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (wall.start.x - wall.end.x) - (ray.start.x - ray.end.x) * (wall.start.x * wall.end.y - wall.start.y * wall.end.x)) / ((ray.start.x - ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x - wall.end.x));

	det.y = ((ray.start.x * ray.end.y - ray.start.y * ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x * wall.end.y - wall.start.y * wall.end.x)) / ((ray.start.x - ray.end.x) * (wall.start.y - wall.end.y) - (ray.start.y - ray.end.y) * (wall.start.x - wall.end.x));
	return (det);
}

double		check_distance(t_player player, t_cast cast, t_wall *w_coords, char **map, char **walltxt, t_wall corners)
{
	t_dvector	walls;
	t_dvector	ray;
	t_vector	result;
	t_vector	med_result;
	t_vector	square;
	int			index;
	int			flag;
	t_vector	start;
	double		distance;
	double		shorter_distance;

	//	printf("ray.x  :%f  ray.y: %f\n", player.ray.x, player.ray.y);
	flag = 0;
	start.x = player.pos.x;
	start.y = player.pos.y;
	square.x = cast.x_pos;
	square.y = cast.y_pos;
	printf("ENTERSESNJDNAWJNSDJNAJDNJA\n\n\n\n\n");
	shorter_distance = -1;
	printf("cast.j: %i cast.i: %i map[cast.j][cast.i]: %c\n", cast.j, cast.i, map[cast.j][cast.i]);
	if (cast.j >= 0 && cast.i >= 0 && map[cast.j][cast.i] && map[cast.j][cast.i] == '+')
	{
		index = -1;
		while (++index < ft_tablen(walltxt))
		{
			walls.start.x = ((double)w_coords[index].start.x - (double)corners.start.x) / (double)(SCREEN_WIDTH / 75);
			walls.start.y = ((double)w_coords[index].start.y - (double)corners.start.y) / (double)(SCREEN_HEIGHT / 75);
			walls.end.x = ((double)w_coords[index].end.x - (double)corners.start.x) / (double)(SCREEN_WIDTH / 75);
			walls.end.y = ((double)w_coords[index].end.y - (double)corners.start.y) / (double)(SCREEN_HEIGHT / 75);
			ray.start.x = player.pos.x;
			ray.start.y = player.pos.y;
			ray.end.x = cast.x_pos;
			ray.end.y = cast.y_pos;
			med_result = intersect_point(ray, walls);
			printf("ray.end.x: %f ray.end.y %f\n walls.start.x: %f walls.start.y: %f walls.end.x: %f walls.end.y: %f", ray.end.x, ray.end.y, walls.start.x, walls.start.y, walls.end.x, walls.end.y); 
			printf("med_result.x: %f, med__result.y %f\n", med_result.x, med_result.y);
		//	printf("cast.i: %i cast.j: %i\n", cast.i, cast.j);
			if (in_segment(med_result, cast) && in_front(ray, cast, med_result) && in_wall(walls, med_result))
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
			//	printf("shorter_distance : %f\n", shorter_distance);
			}
		}
	}
	else if (cast.j >= 0 && cast.i >= 0 && map[cast.j][cast.i] >= 'A' && map[cast.j][cast.i] <= 'Z')
	{
		index = map[cast.j][cast.i] - 65;
		while (index < ft_tablen(walltxt))
		{
			if ((index % 26) == (map[cast.j][cast.i] - 65))
			{
				walls.start.x = ((double)w_coords[index].start.x - (double)corners.start.x) / (double)(SCREEN_WIDTH / 75);
				walls.start.y = ((double)w_coords[index].start.y - (double)corners.start.y) / (double)(SCREEN_HEIGHT / 75);
				walls.end.x = ((double)w_coords[index].end.x - (double)corners.start.x) / (double)(SCREEN_WIDTH / 75);
				walls.end.y = ((double)w_coords[index].end.y - (double)corners.start.y) / (double)(SCREEN_HEIGHT / 75);
				ray.start.x = player.pos.x;
				ray.start.y = player.pos.y;
				ray.end.x = cast.x_pos; //possible error
				ray.end.y = cast.y_pos; // possible error
				med_result = intersect_point(ray, walls);
				printf("index: %i\n", index);
			printf("ray.end.x: %f ray.end.y %f\n walls.start.x: %f walls.start.y: %f walls.end.x: %f walls.end.y: %f\n", ray.end.x, ray.end.y, walls.start.x, walls.start.y, walls.end.x, walls.end.y); 
			printf("med_result.x: %f, med_result.y %f\n", med_result.x, med_result.y);
				printf("cast.i: %i cast.j: %i\n", cast.i, cast.j);
				if (in_segment(med_result, cast) && in_front(ray, cast, med_result) && in_wall(walls, med_result))
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
	else
	{
		printf("Whaaaaaaaaaat?!\n");
		return (0);
	}
	//printf("cast.j :%i cast.i: %i\n", cast.j, cast.i);
	//printf("map thing : %c\n", map[cast.j][cast.i]);
	//printf("shorter_distance: %f\n", shorter_distance);
//	if (shorter_distance <= (distance_calc(start, square)) + 2 && shorter_distance != -1)
	//	return (SCREEN_HEIGHT / (fabs(player.dir.x * (result.x - player.pos.x) + player.dir.y * (result.y - player.pos.y))));
//	else
//	{
		//		printf("BLEH");
//		return (-1);
//	}
	//	printf("shorter_distance: %f\n", shorter_distance);
		return (shorter_distance);
}
