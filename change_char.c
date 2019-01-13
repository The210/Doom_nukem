/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:34:42 by smerelo           #+#    #+#             */
/*   Updated: 2019/01/08 17:34:44 by smerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"doom.h"

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

int       incollision_bb(t_gwall gw_coords, t_vector nextpos)
{
  t_coord to_end;
  t_coord to_player;
  double e;

  e = 0.0000001;
  to_end.x = gw_coords.end.x - gw_coords.start.x > e ? 1 : -1;
  to_end.y = gw_coords.end.y - gw_coords.start.y > e ? 1 : -1;
  gw_coords.start.x -= (double)to_end.x / 3;
  gw_coords.start.y -= (double)to_end.y / 3;
  gw_coords.end.x += (double)to_end.x / 3;
  gw_coords.end.y += (double)to_end.y / 3;
  to_player.x = nextpos.x - gw_coords.start.x > e ? 1 : -1;
  to_player.y = nextpos.y - gw_coords.start.y > e ? 1 : -1;
  if (to_end.x != to_player.x || to_end.y != to_player.y)
    return (0);
  to_end.x = gw_coords.start.x - gw_coords.end.x > e ? 1 : -1;
  to_end.y = gw_coords.start.y - gw_coords.end.y > e ? 1 : -1;
  to_player.x = nextpos.x - gw_coords.end.x > e ? 1 : -1;
  to_player.y = nextpos.y - gw_coords.end.y > e ? 1 : -1;
  if (to_end.x != to_player.x || to_end.y != to_player.y)
    return (0);
  return (1);
}

int       check_collision(t_gwall *gw_coords, t_vector nextpos, int wallslen)
{
  double distance;
  double min_distance;
  double col_distance;
  int i;

  if (nextpos.x <= 0.30 || nextpos.y <= 0.30)
    return (1);
  i = 0;
  col_distance = 0.5;
  distance = (fabs((gw_coords[i].end.y - gw_coords[i].start.y) * (nextpos.x) - (gw_coords[i].end.x - gw_coords[i].start.x) * (nextpos.y) + (gw_coords[i].end.x * gw_coords[i].start.y) - (gw_coords[i].end.y * gw_coords[i].start.x)) / (sqrt(pow(gw_coords[i].end.y - gw_coords[i].start.y, 2) + pow(gw_coords[i].end.x - gw_coords[i].start.x, 2))));
  min_distance = distance;
  while (++i < wallslen)
  {
    if (incollision_bb(gw_coords[i], nextpos))
    {
      distance = (fabs((gw_coords[i].end.y - gw_coords[i].start.y) * (nextpos.x) - (gw_coords[i].end.x - gw_coords[i].start.x) * (nextpos.y) + (gw_coords[i].end.x * gw_coords[i].start.y) - (gw_coords[i].end.y * gw_coords[i].start.x)) / (sqrt(pow(gw_coords[i].end.y - gw_coords[i].start.y, 2) + pow(gw_coords[i].end.x - gw_coords[i].start.x, 2))));
      if (distance < min_distance)
        min_distance = distance;
    }
  }
  return (min_distance >= col_distance ? 0 : 1);
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
    player->wspeed = 0.45;
  if (wind.event.key.keysym.sym == SDLK_s)
    player->sspeed = 0.45;
  if (wind.event.key.keysym.sym == SDLK_d)
    player->dspeed = 0.45;
  if (wind.event.key.keysym.sym == SDLK_a)
    player->aspeed = 0.45;
  if (wind.event.key.keysym.sym == SDLK_LEFT)
    player->thetal = 0.03;
  if (wind.event.key.keysym.sym == SDLK_RIGHT)
    player->thetar = 0.03;
  if (wind.event.key.keysym.sym == SDLK_SPACE && player->jump != -1 && player->crouch != 1)
    player->jump = 1;
  if (wind.event.key.keysym.sym == SDLK_LCTRL && player->jump != 1)
    player->crouch = 1;
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
  if (wind.event.key.keysym.sym == SDLK_LCTRL)
    player->crouch = 0;
}

void mod_char(t_player *player, t_gwall *gw_coords, char **walls)
{
  double temp;
  temp = player->dir.x;
  player->dir.x = cos(player->thetal - player->thetar) * player->dir.x + sin(player->thetal - player->thetar) * player->dir.y;
  player->dir.y = cos(player->thetal - player->thetar) * player->dir.y - sin(player->thetal - player->thetar) * temp;
  player->plane.x = player->dir.y;
  player->plane.y = -player->dir.x;
  if (!(character_collides(player, gw_coords, walls, 1)))
    player->pos.x += (player->wspeed - player->sspeed) * player->dir.x +
                     (player->aspeed - player->dspeed) * player->dir.y;
  if (!(character_collides(player, gw_coords, walls, 0)))
    player->pos.y += (player->wspeed - player->sspeed) * player->dir.y +
                     (player->dspeed - player->aspeed) * player->dir.x;
}

t_player    jump_crouch(t_player player)
{
  if (player.posz < player.jump_height && player.jump == 1)
    player.posz += 10;
  if (player.posz >= player.jump_height)
    player.jump = -1;
  if (player.jump == -1 && player.posz > 0)
    player.posz -= 10;
  if (player.posz == 0 && player.jump == -1)
    player.jump = 0;
  if (player.crouch == 1 && player.posz > player.crouch_height)
    player.posz -= 10;
  if (player.crouch == 0 && player.posz < 0)
    player.posz += 10;
  return (player);
}