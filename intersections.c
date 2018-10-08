/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 20:47:04 by dhorvill          #+#    #+#             */
/*   Updated: 2018/10/08 18:42:51 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vector	normalize(t_vector a)
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

int	main(void)
{
	t_dvector a;
	t_dvector b;
	t_vector result;

	a.start.x = 0;
	a.start.y = 0;
	a.end.x = 0;
	a.end.y = 10;
	b.start.x = 1;
	b.start.y = 0;
	b.end.x = 1;
	b.end.y = 10;
	if (intersects(a,b))
	{
		result = intersect_point(a,b);
		printf("result.x: %f   result.y: %f\n", result.x, result.y);
	}
	else
		printf("Does not intersect\n");
	return (0);
}
