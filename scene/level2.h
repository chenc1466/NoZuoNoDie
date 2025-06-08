#ifndef level2H_INCLUDED
#define level2H_INCLUDED
#include <stdio.h>
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../element/element.h"
#include "../element/charater.h"

#define MAP_WIDTH 80
#define MAP_HEIGHT 46
#define TILE_SIZE 32
/*
   [Set object]
*/
typedef struct _Level2
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;
    int map[MAP_HEIGHT][MAP_WIDTH];
    ALLEGRO_BITMAP *tile_img;
    ALLEGRO_BITMAP *door_img_set;
    ALLEGRO_BITMAP *platform_img_set;
    int door_cnt;
    int door_state;
    int door_move_cnt;
    int platform_move;
    int platform_x;
    int platform_y;


} Level2;
Scene *New_Level2(int label);
void level2_update(Scene *self);
void level2_draw(Scene *self);
void level2_destroy(Scene *self);

#endif
