/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 21:41:43 by snicolet          #+#    #+#             */
/*   Updated: 2018/11/14 22:29:31 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"



unsigned int	get_colors(unsigned int pixel)
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;

	blue = pixel % 256;
	pixel /= 256;
	green = pixel % 256;
	pixel /= 256;
	red = pixel;
	pixel = blue;
	pixel = pixel * 256 + green;
	pixel = pixel * 256 + red;
	printf("new_pixel: %#X\n", pixel);
	return (pixel);
}

static void			*load_tga_error(const char *error, void *file_content)
{
	if (file_content)
		free(file_content);
	ft_putendl(error);
	return (NULL);
}

static unsigned int	*pixels_to_rgba(unsigned int *pixels, size_t n)
{
	size_t p = n -1;
	while (n--)
	{
		pixels[n] = TGA_L(pixels[n]);
	printf("pixels[n]: %#X\n", pixels[n]);
		pixels[n] = get_colors(pixels[n]);
	}
	return (pixels);
}

static size_t	ft_filesize(const char *filepath)
{
	struct stat		st;

	if (stat(filepath, &st) != 0)
		return (0);
	return ((size_t)st.st_size);
}

char			*ft_readfile(const char *filepath, size_t *usize)
{
	const size_t	size = ft_filesize(filepath);
	ssize_t			ret;
	int				fd;
	char			*data;

	data = NULL;
	if ((!size) || (!(data = malloc(sizeof(char) * (size + 1)))) ||
			(!(fd = open(filepath, O_RDONLY))))
	{
		if (usize)
			*usize = 0;
		if (data)
			free(data);
		return (NULL);
	}
	ret = read(fd, data, size);
	data[ret] = '\0';
	close(fd);
	if (usize)
		*usize = size;
	return (data);
}

static unsigned int	*tga_px3(unsigned char *pixels, const t_tga *specs)
{
	const size_t		pixels_total = specs->width * specs->height;
	const size_t		size = pixels_total * 3;
	size_t				p;
	unsigned int		*buffer;
	unsigned int		*px;

	if (!(buffer = malloc(pixels_total * 4)))
		return (load_tga_error("failed to alloc the second stage", pixels));
	px = buffer;
	p = 0;
	while (p < size)
	{
		//printf("p:%#X p+1:%#x p+2:%#X\n", pixels[p], pixels[p + 1], pixels[p + 2]);
		*(px++) = ((unsigned int)0xff << 24) |
			((unsigned int)pixels[p]) |
			((unsigned int)pixels[p + 1] << 8) |
			((unsigned int)pixels[p + 2] << 16);
		p += 3;
	}
	free(pixels);
	return (buffer);
}

/*
 ** load a tga file into a unsigned int * to retrive pixels,
 ** *specs will be filled by the function, in case of error each value will be
 ** set to 0 and NULL will be returned
 */

unsigned int		*tga_load(const char *filepath, t_tga *specs)
{
	size_t			file_size;
	size_t			pixels_size;
	unsigned int	*pixels;
	char			*file_content;
	t_tga			*header;

	ft_bzero(specs, TGA_SIZE);
	if(!(file_content = ft_readfile(filepath, &file_size)))
		return (load_tga_error("unable to read file\n", NULL));
	if (file_size <= TGA_SIZE)
		return (load_tga_error("invalid file or no content\n", file_content));
	header = (t_tga*)(size_t)file_content;
	if ((header->type != TGA_TYPE_TC_RAW) || (header->depth < 24))
		return (load_tga_error("unsupported file format\n", file_content));
	pixels_size = header->width * header->height * (header->depth >> 3) + 1;
	//printf("%lu - %lu\n", pixels_size, file_size - TGA_SIZE);
	if ((pixels = malloc(pixels_size)))
	{
		ft_memcpy(pixels, &file_content[TGA_SIZE], pixels_size);
		*specs = *header;
		free(file_content);
		if (specs->depth == 24)
			return (tga_px3((void*)(size_t)pixels, specs));
		return (pixels_to_rgba(pixels, specs->height * specs->width));
	}
	return (load_tga_error("failed to get pixels\n", file_content));
}
/*int			main(int ac, char **av)
{
	t_tga specs;
	unsigned int *pixels;
	int i;
	int j;
	int iprime;
	int	jprime;
	double	size;
	unsigned int *res_img;
	t_wind wind;

	i = -1;
	size = 501;
	iprime = size - 1;
	wind = init_wind(wind);
	pixels = tga_load("download.tga", &specs);
	res_img = resize(pixels, specs, size);
	while (1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_KEYDOWN)
			{
				check_keydown(wind);
				return (0);
			}
			while (++i < size - 1)
			{
				j = -1;
				jprime = 0;
				while (++j < size - 1)
				{
					put_pixel32(wind.screen, j, i, (Uint32)res_img[iprime * (int)size + jprime] - 0xFF000000);
					jprime++;
				}
				iprime--;
			}
		}
		SDL_UpdateWindowSurface(wind.window);
	}

	return (0);
}*/
