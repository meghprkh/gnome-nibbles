/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*- */

/*
 *   Gnome Nibbles: Gnome Worm Game
 *   Written by Sean MacIsaac <sjm@acm.org>, Ian Peters <itp@gnu.org>,
 *              Guillaume Beland <guillaume.beland@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <config.h>

#include <stdlib.h>

#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>

#include "gnibbles.h"
#include "bonus.h"
#include "properties.h"
#include "board.h"

extern GdkPixbuf *boni_pixmaps[];
extern GnibblesProperties *properties;
extern GnibblesBoard *board;
extern ClutterActor *stage;

GnibblesBonus *
gnibbles_bonus_new (gint t_x, gint t_y, gint t_type,
                    gint t_fake, gint t_countdown)
{
  GnibblesBonus *tmp;

  tmp = g_new (GnibblesBonus, 1);

  tmp->x = t_x;
  tmp->y = t_y;
  tmp->type = t_type;
  tmp->fake = t_fake;
  tmp->countdown = t_countdown;
  tmp->actor = gtk_clutter_texture_new ();
  return (tmp);
}

void
gnibbles_bonus_draw (GnibblesBonus *bonus)
{
  GError *err = NULL;

  clutter_actor_set_position (CLUTTER_ACTOR (bonus->actor),
                              bonus->x * properties->tilesize,
                              bonus->y * properties->tilesize);

  gtk_clutter_texture_set_from_pixbuf (GTK_CLUTTER_TEXTURE (bonus->actor),
                                       boni_pixmaps[bonus->type],
                                       &err);
  if (err)
    gnibbles_error (err->message);

  clutter_actor_add_child (stage, bonus->actor);

  clutter_actor_set_opacity (bonus->actor, 0);
  clutter_actor_set_scale (bonus->actor, 3.0, 3.0);

  clutter_actor_save_easing_state (bonus->actor);
  clutter_actor_set_easing_mode (bonus->actor, CLUTTER_EASE_OUT_BOUNCE);
  clutter_actor_set_easing_duration (bonus->actor, GAMEDELAY * 20);
  clutter_actor_set_scale (bonus->actor, 1.0, 1.0);
  clutter_actor_set_pivot_point (bonus->actor,.5,.5); 
  clutter_actor_set_opacity (bonus->actor, 0xff);
  clutter_actor_restore_easing_state (bonus->actor);

}

void
gnibbles_bonus_erase (GnibblesBonus *bonus)
{
  clutter_actor_hide (bonus->actor);
}