#include "doom.h"

t_gwall    *createGameWalls(t_wall *w_coords, char **walls, t_wall corners)
{
  int i;
  int wallslen;
  t_gwall *gw_coords;

  i = -1;
  if ((gw_coords = (t_gwall*)malloc(sizeof(t_gwall) * (ft_tablen(walls) + 1) * 10)) == 0)
		gw_coords[0].error = 1;
  wallslen = ft_tablen(walls);
  while (++i < wallslen)
  {
    gw_coords[i].start.x = (double)w_coords[i].start.x / (double)(SCREEN_WIDTH / 50) - (double)corners.start.x;
    gw_coords[i].start.y = (double)w_coords[i].start.y / (double)(SCREEN_HEIGHT / 50) - (double)corners.start.y;
    gw_coords[i].end.x = (double)w_coords[i].end.x / (double)(SCREEN_WIDTH / 50) - (double)corners.start.x;
    gw_coords[i].end.y = (double)w_coords[i].end.y / (double)(SCREEN_HEIGHT / 50) - (double)corners.start.y;
  }
  return (gw_coords);
}

int       check_collision(t_gwall *gw_coords, t_vector nextpos, int wallslen)
{
  double distance;
  double min_distance;
  double col_distance;
  int i;

  if (nextpos.x <= 0.5 || nextpos.y <= 0.5 || nextpos.y > wallslen)
    return (1);
  i = 0;
  col_distance = 0.05;
  distance = (fabs((gw_coords[i].end.y - gw_coords[i].start.y) * (nextpos.x) - (gw_coords[i].end.x - gw_coords[i].start.x) * (nextpos.y) + (gw_coords[i].end.x * gw_coords[i].start.y) - (gw_coords[i].end.y * gw_coords[i].start.x)) / (sqrt(pow(gw_coords[i].end.y - gw_coords[i].start.y, 2) + pow(gw_coords[i].end.x - gw_coords[i].start.x, 2))));
  min_distance = distance;
  while (++i < wallslen)
  {
    distance = (fabs((gw_coords[i].end.y - gw_coords[i].start.y) * (nextpos.x) - (gw_coords[i].end.x - gw_coords[i].start.x) * (nextpos.y) + (gw_coords[i].end.x * gw_coords[i].start.y) - (gw_coords[i].end.y * gw_coords[i].start.x)) / (sqrt(pow(gw_coords[i].end.y - gw_coords[i].start.y, 2) + pow(gw_coords[i].end.x - gw_coords[i].start.x, 2))));
    if (distance < min_distance)
    min_distance = distance;
  }
  return (min_distance >= col_distance? 0 : 1);
}

int       character_collides(t_player *player, t_gwall *gw_coords, char **walls, int axis)
{
  t_vector nextpos;
  int wallslen;

  wallslen = ft_tablen(walls);
  if (axis)
  {
    nextpos.x = player->pos.x + (player->wspeed - player->sspeed) * player->dir.x
  	+ (player->aspeed - player->dspeed) * player->dir.y;
    nextpos.y = player->pos.y;
  }
  else
  {
    nextpos.x = player->pos.x;
    nextpos.y = player->pos.y + (player->wspeed - player->sspeed) * player->dir.y
    + (player->dspeed - player->aspeed) * player->dir.x;
  }
  return (check_collision(gw_coords, nextpos, wallslen));

}

int      check_char_down(t_player *player, t_wind wind)
{
  if (wind.event.key.keysym.sym == SDLK_ESCAPE)
  {
    SDL_DestroyWindow(wind.window);
    SDL_Quit();
    return (0);
  }
  if (wind.event.key.keysym.sym == SDLK_w)
    player->wspeed = 0.1;
  if (wind.event.key.keysym.sym == SDLK_s)
    player->sspeed = 0.1;
  if (wind.event.key.keysym.sym == SDLK_d)
    player->dspeed = 0.1;
  if (wind.event.key.keysym.sym == SDLK_a)
    player->aspeed = 0.1;
  if (wind.event.key.keysym.sym == SDLK_LEFT)
    player->thetal = 0.03;
  if (wind.event.key.keysym.sym == SDLK_RIGHT)
    player->thetar = 0.03;
  return (1);
}

void  reset_char(t_player *player, t_wind wind)
{
  if (wind.event.key.keysym.sym == SDLK_w)
    player->wspeed = 0;
  if (wind.event.key.keysym.sym == SDLK_s)
    player->sspeed = 0;
  if (wind.event.key.keysym.sym == SDLK_d)
    player->dspeed = 0;
  if (wind.event.key.keysym.sym == SDLK_a)
    player->aspeed = 0;
  if (wind.event.key.keysym.sym == SDLK_LEFT)
    player->thetal = 0;
  if (wind.event.key.keysym.sym == SDLK_RIGHT)
    player->thetar = 0;
}

void mod_char(t_player *player, t_gwall *gw_coords, char **walls)
{
  double temp;
  temp = player->dir.x;
  player->dir.x = cos(player->thetal - player->thetar) * player->dir.x + sin(player->thetal - player->thetar) * player->dir.y;
  player->dir.y = cos(player->thetal - player->thetar) * player->dir.y - sin (player->thetal - player->thetar) * temp;
  player->plane.x = player->dir.y;
  player->plane.y = -player->dir.x;
  if (!(character_collides(player, gw_coords, walls, 1)))
    player->pos.x += (player->wspeed - player->sspeed) * player->dir.x +
                         (player->aspeed - player->dspeed) * player->dir.y;
  if (!(character_collides(player, gw_coords, walls, 0)))
    player->pos.y += (player->wspeed - player->sspeed) * player->dir.y +
                         (player->dspeed - player->aspeed) * player->dir.x;
}
