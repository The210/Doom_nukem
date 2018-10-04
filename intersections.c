/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:59:29 by dhorvill          #+#    #+#             */
/*   Updated: 2018/10/04 19:15:18 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
	ray = E = B-A = ( Bx-Ax, By-Ay )
	line = F = D-C = ( Dx-Cx, Dy-Cy ) 
		P = ( -Ey, Ex )
		h = ((A-C) * P ) / ( F * P )

double	dot_product(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x * b.x;
	reslut.y = a.y * b.y;
	return (result.x + result.y);
}

t_vector	sub_vect(t_vector a, t_vector b)
{
	t_vector result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

t_vector	add_vector(t_vector a, _vector b)
{
	t_vector	result;
}

int	intersects(t_wall ray, t_wall line)
{
	t_vector	nu;
	double		distance;

	nu.y = ray.start.y - ray.end.y;
	nu.x = ray.end.x - ray.start.x;
	

}
