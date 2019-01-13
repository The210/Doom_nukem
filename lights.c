#include "doom.h"

char    **read_lights(t_fd fd)
{
  char *buf;
  int  ret;
  char *str;
  char **lightmap;

  str = ft_strnew(1);
  close(fd.lights);
  fd.lights = open("lights.txt",O_RDONLY);
  while ((ret = get_next_line(fd.lights, &buf)) == 1)
  {
    str = ft_strjoin(str, buf);
    ft_strdel(&buf);
  }
  if ((lightmap = ft_strsplit(str, ' ')) == NULL || ret == -1)
  {
    ft_putendl("error");
    return (NULL);
  }
  return (lightmap);
}

t_light    *separate_lights(t_light *lights, char **lightmap)
{
  int count;
  int lightslen;
  int i;
  int j;

  lightslen = ft_tablen(lightmap);
  i = -1;
  lights = (t_light*)malloc(sizeof(lights) * (lightslen + 1) * 10);
  lights[0].map = lightmap;
  ft_strdel(lightmap);
  while (lights[0].map[++i])
  {
    j = 0;
    count = 0;
    while (lights[0].map[i][j])
    {
			while(lights[0].map[i][j] && (lights[0].map[i][j] != '-' && (lights[0].map[i][j] < '0' || lights[0].map[i][j] > '9')))
				j++;
			if (count == 0)
				lights[i].pos.x = ft_iatoi(lights[0].map[i], j);
			else if (count == 1)
				lights[i].pos.y = ft_iatoi(lights[0].map[i], j);
			else if (count == 2)
				lights[i].intensity = ft_iatoi(lights[0].map[i], j);
			while (lights[0].map[i][j] && ((lights[0].map[i][j] >= '0' && lights[0].map[i][j] <= '9') || lights[0].map[i][j] == '-'))
				j++;
			count++;
		}
    lights[i].rect.x = lights[i].pos.x - lights[i].intensity / 2;
    lights[i].rect.y = lights[i].pos.y - lights[i].intensity / 2;
    lights[i].rect.h = lights[i].intensity;
    lights[i].rect.w = lights[i].intensity;
    lights[i].color = 0xffffff;
	}
	return (lights);
}

t_light   *update_lights(t_light *lights, t_fd fd)
{
  char **lightmap;
  lightmap = read_lights(fd);
  lights = separate_lights(lights, lightmap);
  return(lights);
}

void   re_draw_lights(t_wind wind, t_light *lights, t_coord map_offset)
{
  int i;
  int lightslen;

  i = -1;
  lightslen = ft_tablen(lights[0].map);
  while(++i < lightslen)
    SDL_FillRect(wind.screen, &lights[i].rect, lights->color);
}

void    draw_light(t_wind wind, t_light light)
{
  SDL_FillRect(wind.screen, &light.rect, light.color);
}

void    w_light_coords(t_coord start, t_coord end, t_fd fd, t_coord offset)
{
  double length;

  length = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
  if(length >= 5)
  {
    ft_putnbr_fd(start.x - offset.x, fd.lights);
    ft_putchar_fd('.', fd.lights);
    ft_putnbr_fd(start.y - offset.y, fd.lights);
    ft_putchar_fd(':', fd.lights);
    if (length >= 100)
      ft_putnbr_fd(100, fd.lights);
    else
      ft_putnbr_fd(length, fd.lights);
    ft_putchar_fd('\n', fd.lights);
  }
}
