/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 23:59:24 by dhorvill          #+#    #+#             */
/*   Updated: 2018/09/11 03:04:26 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_grid(t_wind wind, t_coord mouse_pos, t_coord offset, t_coord map_offset)
{
	t_line line;
	t_coord point;
	t_coord next_point;
	int i;
	int j;

	i = -1;
	point.x = 0;
	next_point.x = SCREEN_WIDTH - 1;
	while (++i < SCREEN_HEIGHT)
	{
		if ((offset.y % (SCREEN_HEIGHT / 75)) == 0)
		{
			if (offset.y % 10 == 0)
				line.color = 0x8e8b8b;
			else
				line.color = 0x5d6263;
			point.y = i;
			next_point.y = i;
			ft_draw_line2(wind, point, next_point, line);
		}
		offset.y++;
	}
	point.y = 0;
	next_point.y = SCREEN_HEIGHT - 1;
	i = 0;
	while (++i < SCREEN_WIDTH)
	{
		if ((offset.x % (SCREEN_WIDTH / 75)) == 0)
		{
			if (offset.x % 10 == 0)
				line.color = 0x8e8b8b;
			else
				line.color = 0x5d6263;
			point.x = i;
			next_point.x = i;
			ft_draw_line2(wind, point, next_point, line);
		}
		offset.x++;
	}
	line.color = 0xFFFFFF;
}
