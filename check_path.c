/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 21:51:07 by dhorvill          #+#    #+#             */
/*   Updated: 2018/12/01 00:47:11 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				in_liner(t_coord start, t_coord end, t_vector temp_coords)
{
	double dis1;
	double dis2;
	t_vector temps;
	t_vector temp;

	temps.x = start.x;
	temps.y = start.y;
	temp.x = end.x;
	temp.y = end.y;

	dis1 = sqrt(pow(temp.x - temps.x, 2) + pow(temp.y - temps.y, 2));
	if (dis1 <= 0)
		return(0);
	dis2 = sqrt(pow(temp_coords.x - temps.x, 2) + pow(temp_coords.y - temps.y, 2));
	return(dis1 >= dis2 ? 1 : 0);
}

void			line_path(t_coord start, t_coord end, t_fd fd)
{

	double		slope;
	t_vector	delta1;
	t_vector	delta2;
	t_vector	temp_coord;
	t_vector	temp;
	t_coord		map_coord;
	int			flag;

	flag = 0;
	temp_coord.x = start.x;
	temp_coord.y = start.y;
	delta1.x = end.x - temp_coord.x;
	delta1.y = end.y - temp_coord.y;
	slope = delta1.y / delta1.x;
	if (delta1.x == 0)
	{
		while ((in_liner(start, end, temp_coord) == 1))
		{
			if (flag != 0)
				ft_putchar_fd(':', fd.squares);
			flag = 1;
			map_coord.x = (temp_coord.x) / (SCREEN_HEIGHT / 50);
			map_coord.y = (temp_coord.y) / (SCREEN_WIDTH / 50);
			ft_putnbr_fd(map_coord.x, fd.squares);
			ft_putchar_fd('.', fd.squares);
			ft_putnbr_fd(map_coord.y, fd.squares);
			if (delta1.y > 0)
				temp_coord.y = temp_coord.y - ((int)temp_coord.y % (SCREEN_HEIGHT / 50)) + (SCREEN_HEIGHT / 50);
			if(delta1.y < 0)
				temp_coord.y = temp_coord.y + ((-(int)temp_coord.y) % (SCREEN_HEIGHT / 50)) - (SCREEN_HEIGHT / 50);
		}
	}
	else
	{
		while ((in_liner(start, end, temp_coord) == 1))
		{
			if (flag == 1)
				ft_putchar_fd(':', fd.squares);
			flag = 1;
			map_coord.x = (temp_coord.x) / (SCREEN_HEIGHT / 50);
			map_coord.y = (temp_coord.y) / (SCREEN_WIDTH / 50);
			ft_putnbr_fd(map_coord.x, fd.squares);
			ft_putchar_fd('.', fd.squares);
			ft_putnbr_fd(map_coord.y, fd.squares);
			if (map_coord.x > 900)
				break;
			if (delta1.x < 0)
				temp.x = temp_coord.x + ((-(int)temp_coord.x) % (SCREEN_WIDTH / 50)) - (SCREEN_WIDTH / 50);
			if (delta1.x > 0)
				temp.x = temp_coord.x - ((int)temp_coord.x % (SCREEN_WIDTH / 50)) + (SCREEN_WIDTH / 50);
			if (delta1.y < 0)
				temp.y = temp_coord.y + ((-(int)temp_coord.y) % (SCREEN_HEIGHT / 50)) - (SCREEN_HEIGHT / 50);
			if (delta1.y > 0)
				temp.y = temp_coord.y - ((int)temp_coord.y % (SCREEN_HEIGHT / 50)) + (SCREEN_HEIGHT / 50);
			delta2.y = temp.y - temp_coord.y;
			delta2.x = temp.x - temp_coord.x;
			if ((fabs(fabs(delta2.y / delta2.x) - fabs(slope))) < 0.000001)
			{
				temp_coord.x += delta2.x;
				temp_coord.y += delta2.y;
			}
			else if (fabs(delta2.y / delta2.x) < fabs(slope))
			{
				temp_coord.x += delta2.y / slope;
				temp_coord.y += delta2.y;
			}
			else 
			{
				temp_coord.x = temp_coord.x + delta2.x;
				temp_coord.y = temp_coord.y + slope * delta2.x;
			}
		}
	}
	ft_putchar_fd('\n', fd.squares);
}
