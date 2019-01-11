/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:14:40 by smerelo           #+#    #+#             */
/*   Updated: 2018/11/14 22:29:30 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned int *resize(unsigned int *pixels, t_tga specs, double size)
{
	unsigned int *res_img;
	double prop;
	double i;
	double j;
	int	res_i;
	int res_j;

	j = 0;
	res_j = 0;
	prop = specs.width / size;
	if ((res_img = (unsigned int *)malloc((sizeof(res_img)) * size * size)) == 0)
		return (0);
	while (j < specs.height)
	{
		res_i = 0;
		i = 0;
		while (i < specs.width)
		{
			res_img[res_j * (int)size + res_i] = pixels[(int)j * specs.width + (int)i];
			i += prop;
			res_i++;
		}
		if (i > specs.width)
			res_img[res_j * (int)size + res_i] = pixels[(int)j * specs.width + specs.width - 1];
		j += prop;
		res_j++;
	}
	return(res_img);
}
