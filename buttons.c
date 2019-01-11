/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 21:11:57 by smerelo           #+#    #+#             */
/*   Updated: 2018/12/03 20:38:22 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void    draw_vertical(int size, int posx, int posy, t_wind wind)
{
	int y;

	y = -1;
	while (++y < size)
		put_pixel32(wind.screen, posx, posy + y, 0xffff00);
}

void    draw_horizontal(int size, int posx, int posy, t_wind wind)
{
	int x;

	x = -1;
	while (++x < size)
		put_pixel32(wind.screen, posx + x, posy, 0xffff00);
}

void    display_select(t_button button, t_wind wind)
{
	draw_horizontal(button.size, button.pos_x, button.pos_y, wind);
	draw_horizontal(button.size, button.pos_x, button.pos_y + button.size, wind);
	draw_vertical(button.size, button.pos_x, button.pos_y, wind);
	draw_vertical(button.size, button.pos_x + button.size, button.pos_y, wind);
}

int		in_button_d(t_coord mouse_pos, t_button *button)
{
	int i;
	int	match;

	match = -1;
	i = -1;
	while(++i < button[0].len)
	{
		if(mouse_pos.x >= button[i].pos_x && mouse_pos.x <= button[i].pos_x + button[i].size && mouse_pos.y >= button[i].pos_y && mouse_pos.y <= button[i].pos_y + button[i].size)
		{
			match = i;
			break;
		}
	}
	return (match != -1 ? i : -1);
}

int		in_button_u(t_coord mouse_pos, t_button *button, int index, int c_button)
{
	if ( mouse_pos.x >= button[index].pos_x && mouse_pos.x <= button[index].pos_x + button[index].size && mouse_pos.y >= button[index].pos_y && mouse_pos.y <= button[index].pos_y + button[index].size)
		return (index);
	else
		return (c_button);
}

char		**read_buttons(t_fd fd)
{
	char	*buf;
	int		ret;
	char	**buttons;
	char	*str;

	str = ft_strnew(1);
	close(fd.walls);
	fd.buttonss = open("buttons.txt", O_RDONLY);
	while ((ret = get_next_line(fd.buttonss, &buf)) == 1)
	{
		str = ft_strjoin2(str, buf);
		ft_strdel(&buf);
	}
	if ((buttons = ft_strsplit(str, ' ')) == NULL || ret == -1)
	{
		ft_putendl("error");
		return (NULL);
	}
	return (buttons);
}

void	display_img(t_button button, t_wind wind)
{
	int i;
	int j;
	int	iprime;
	int	jprime;

	i = -1;
	iprime = button.size -1;
	while (++i < button.size - 1)
	{
		j = -1;
		jprime = 0;
		while (++j < button.size - 1)
		{
			if (i + button.pos_y < SCREEN_HEIGHT && j + button.pos_x < SCREEN_WIDTH && i+ button.pos_y >= 0 && j + button.pos_x >= 0)
				put_pixel32(wind.screen, j + button.pos_x, i + button.pos_y, (Uint32)button.img[iprime * (int)button.size + jprime] - 0xFF000000);
			jprime++;
		}
		iprime--;
	}
}

void	display_buttons(t_button *buttons, t_wind wind)
{
	int i;
	i = -1;
	while (++i < buttons[0].len)
	{
		display_img(buttons[i], wind);
		if (buttons[i].select)
			display_select(buttons[i], wind);
	}
}

t_button	fill_button(t_button button)
{
	unsigned int	*pixels;
	t_tga 			specs;

	pixels = tga_load(button.name, &specs);
	button.img = resize(pixels, specs, button.size);
	free(pixels);
	return(button);
}

void	buttons(t_button button, t_fd fd)
{

	fd.buttonss = open("buttons.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	ft_putnbr_fd(button.pos_x, fd.buttonss);
	ft_putchar_fd('.', fd.buttonss);
	ft_putnbr_fd(button.pos_y, fd.buttonss);
	ft_putchar_fd(':', fd.buttonss);
	ft_putnbr_fd(button.size, fd.buttonss);
	ft_putchar_fd(':', fd.buttonss);
	ft_putendl_fd(button.name, fd.buttonss);
}

double			ft_iatod(char *wall, int index)
{
	double number;
	int i;
	double	negative;

	i = index;
	negative = 1;
	number = 0;
	if (wall[index] == '-')
	{
		i++;
		negative = -1;
	}
	while (wall[i] && wall[i] >= '0' && wall[i] <= '9')
	{
		number = number * 10 + wall[i] - '0';
		i++;
	}
	return (number * negative);
}

char	*read_name(char *str, int	index)
{
	int 	i;
	int		size;
	char	*name;

	i = index;
	while (str[i])
		i++;
	size = i - index + 1;
	if ((name = (char*)malloc(sizeof(name) * size)) == 0)
		return (NULL);
	name[size] = '\0';
	i = 0;
	while (str[index])
	{
		name[i] = str[index];
		index++;
		i++;
	}
	name[i] = '\0';
	return (name);
}

t_button	*fill_all(t_fd fd)
{
	t_button	*buttons;
	char		**b_char;
	int			count;
	int			i;
	int			j;

	fd.buttonss = open("buttons.txt", O_RDWR | O_APPEND);
	b_char = read_buttons(fd);
	buttons = (t_button*)malloc(sizeof(buttons) * (ft_tablen(b_char) + 10));
	i = 0;
	while (b_char[i])
	{
		j = 0;
		count = 0;
		while (b_char[i][j])
		{
			while (b_char[i][j] && (b_char[i][j] == '.' || b_char[i][j] == ':'))
				j++;
			if (count == 0)
				buttons[i].pos_x = ft_iatoi(b_char[i], j);
			else if (count == 1)
				buttons[i].pos_y = ft_iatoi(b_char[i], j);
			else if (count == 2)
				buttons[i].size = ft_iatod(b_char[i], j);
			else if (count == 3)
				buttons[i].name = read_name(b_char[i], j);
			while (b_char[i][j] && b_char[i][j] != '.' && b_char[i][j] != ':')
				j++;
			count++;
		}
		buttons[i] = fill_button(buttons[i]);
		i++;
	}
	buttons[0].len = i;
	return (buttons);
}
