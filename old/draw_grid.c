/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 23:59:24 by dhorvill          #+#    #+#             */
/*   Updated: 2018/11/11 22:08:36 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*void		draw_grid(t_wind wind, t_coord mouse_pos, t_coord offset)
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
	i = -1;
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
}*/





void	draw_grid(t_wind wind, t_coord mouse_pos, t_coord offset)
{
	t_line	line;
	t_coord	point;
	t_coord	next_point;
	int	i;
	int	j;
	t_coord	in_offset;

	j = -1;
	in_offset = offset;
	point.x = 0;
	next_point.x = SCREEN_WIDTH - 1;
	while (++j < SCREEN_HEIGHT)
	{
		if (in_offset.y % (SCREEN_HEIGHT / 75) == 0)
		{
			if (in_offset.y % 10 == 0)
				line.color = 0x8E8B8B;
			else
				line.color = 0x5D6263;
			point.y = j;
			next_point.y = j;
			ft_draw_line2(wind, point, next_point, line);
		}
		in_offset.y++;
	}
	point.y = 0;
	next_point.y = SCREEN_HEIGHT - 1;
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		if (in_offset.x % (SCREEN_WIDTH / 75) == 0)
		{
			if (in_offset.x % 10 == 0)
				line.color = 0x8E8B8B;
			else
				line.color = 0x5D6263;
			point.x = i;
			next_point.x = i;
			ft_draw_line2(wind, point, next_point, line);
		}
		in_offset.x++;
	}
}
