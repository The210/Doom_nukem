/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 21:49:52 by smerelo           #+#    #+#             */
/*   Updated: 2018/09/11 01:51:47 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	change_point(t_coord *point, t_coord *next_point, t_line line)
{
	point->x += line.offset.x;
	point->y += line.offset.y;
	next_point->x += line.offset.x;
	next_point->y += line.offset.y;
}

t_line	mdy(t_wind wind, t_coord point, t_coord next_point, t_line line)
{
	line.m = line.dy / line.dx;
	line.pb = point.y - line.m * point.x;
	while (point.x != next_point.x)
	{
		line.intm = round(line.m * point.x + line.pb);
		if (point.x < 1250 && line.intm < 1250
				&& point.x >= 0 && line.intm >= 0)
			put_pixel32(wind.screen, point.x, line.intm, line.color);
		point.x += line.sx;
	}
	return (line);
}

t_line	mdx(t_wind wind, t_coord point, t_coord next_point, t_line line)
{
	line.m = line.dx / line.dy;
	line.pb = point.x - line.m * point.y;
	while (point.y != next_point.y)
	{
		line.intb = round(line.m * point.y + line.pb);
		if (line.intb < 1250 && point.y < 1250
				&& line.intb >= 0 && point.y >= 0)
			put_pixel32(wind.screen, line.intb, point.y, line.color);
		point.y += line.sy;
	}
	return (line);
}

int			ft_draw_line2(t_wind wind, t_coord point, t_coord next_point, t_line line)
{
	change_point(&point, &next_point, line);
	if (point.x == next_point.x && point.y == next_point.y)
	{
		if (point.x < 1250 && point.y < 1250 && point.x >= 0 && point.y >= 0)
			put_pixel32(wind.screen, point.x, point.y, line.color);
		return (0);
	}
	line.dx = next_point.x - point.x;
	line.dy = next_point.y - point.y;
	line.sx = (line.dx < 0) ? -1 : 1;
	line.sy = (line.dy < 0) ? -1 : 1;
	if (fabsf(line.dy) < fabsf(line.dx))
		line = mdy(wind, point, next_point, line);
	else
		line = mdx(wind, point, next_point, line);
	if (next_point.x < 1250 && next_point.y < 1250 &&
			next_point.x >= 0 && next_point.y >= 0)
		put_pixel32(wind.screen, next_point.x, next_point.y, 0x5d6263);
	return (0);
}
