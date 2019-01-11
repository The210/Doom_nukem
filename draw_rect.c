/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:06:22 by smerelo           #+#    #+#             */
/*   Updated: 2018/12/01 00:47:18 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		write_rect(t_wall rect_pos, t_coord map_offset, t_fd fd)
{
		
		close(fd.walls);
		fd.walls = open("walls.txt", O_RDWR | O_APPEND);
		t_coord ln_start;
		t_coord ln_end;

		ft_putnbr_fd(rect_pos.start.x - map_offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(rect_pos.start.y - map_offset.y, fd.walls);
		ft_putchar_fd(':', fd.walls);
		ft_putnbr_fd(rect_pos.end.x - map_offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(rect_pos.start.y - map_offset.y, fd.walls);
		ft_putchar_fd('\n', fd.walls);
		ln_start.x = rect_pos.start.x - map_offset.x;
		ln_start.y = rect_pos.start.y - map_offset.y;
		ln_end.x = rect_pos.end.x - map_offset.x;
		ln_end.y = rect_pos.start.y - map_offset.y;
		line_path(ln_start, ln_end, fd);
		ft_putnbr_fd(rect_pos.start.x - map_offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(rect_pos.start.y - map_offset.y, fd.walls);
		ft_putchar_fd(':', fd.walls);
		ft_putnbr_fd(rect_pos.start.x - map_offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(rect_pos.end.y - map_offset.y, fd.walls);
		ft_putchar_fd('\n', fd.walls);
		ln_start.x = rect_pos.start.x - map_offset.x;
		ln_start.y = rect_pos.start.y - map_offset.y;
		ln_end.x = rect_pos.start.x - map_offset.x;
		ln_end.y = rect_pos.end.y - map_offset.y;
		line_path(ln_start, ln_end, fd); 
		ft_putnbr_fd(rect_pos.start.x - map_offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(rect_pos.end.y - map_offset.y, fd.walls);
		ft_putchar_fd(':', fd.walls);
		ft_putnbr_fd(rect_pos.end.x - map_offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(rect_pos.end.y - map_offset.y, fd.walls);
		ft_putchar_fd('\n', fd.walls);
		ln_start.x = rect_pos.start.x - map_offset.x;
		ln_start.y = rect_pos.end.y - map_offset.y;
		ln_end.x = rect_pos.end.x - map_offset.x;
		ln_end.y = rect_pos.end.y - map_offset.y;
		line_path(ln_start, ln_end, fd);
		ft_putnbr_fd(rect_pos.end.x - map_offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(rect_pos.start.y - map_offset.y, fd.walls);
		ft_putchar_fd(':', fd.walls);
		ft_putnbr_fd(rect_pos.end.x - map_offset.x, fd.walls);
		ft_putchar_fd('.', fd.walls);
		ft_putnbr_fd(rect_pos.end.y - map_offset.y, fd.walls);
		ft_putchar_fd('\n', fd.walls);
		ln_start.x = rect_pos.end.x - map_offset.x;
		ln_start.y = rect_pos.start.y - map_offset.y;
		ln_end.x = rect_pos.end.x - map_offset.x;
		ln_end.y = rect_pos.end.y - map_offset.y;
		line_path(ln_start, ln_end, fd);
}


void		draw_rect(t_wind wind, t_wall rect_pos)
{
	int w;
	int l;
	t_line line;
	t_coord p;
	t_coord np;

	w = abs(rect_pos.end.x - rect_pos.start.x);
	l = abs(rect_pos.end.y - rect_pos.start.y);
	line.color = 0xFFFFFF;
	p.x = rect_pos.start.x;
	p.y = rect_pos.start.y;
	np.x = rect_pos.end.x;
	np.y = rect_pos.start.y;
	ft_draw_line3(wind, p, np, line);
	p.x = rect_pos.start.x;
	p.y = rect_pos.start.y;
	np.x = rect_pos.start.x;
	np.y = rect_pos.end.y;
	ft_draw_line3(wind, p, np, line);
	p.x = rect_pos.start.x;
	p.y = rect_pos.end.y;
	np.x = rect_pos.end.x;
	np.y = rect_pos.end.y;
	ft_draw_line3(wind, p, np, line);
	p.x = rect_pos.end.x;
	p.y = rect_pos.start.y;
	np.x = rect_pos.end.x;
	np.y = rect_pos.end.y;
	ft_draw_line3(wind, p, np, line);
}
