#ifndef level1H_INCLUDED
#define level1H_INCLUDED
#include <stdio.h>
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../element/element.h"
#include "../element/charater.h"

#define MAP_WIDTH 80
#define MAP_HEIGHT 45
#define TILE_SIZE 32

/*
   [Set object]
*/
typedef struct _Level1
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;
    int map[MAP_HEIGHT][MAP_WIDTH];
    ALLEGRO_BITMAP *tile_img;
    ALLEGRO_BITMAP *door_img_set;
    ALLEGRO_BITMAP *spine_img;
    int door_cnt;
    int door_state;
    int door_move_cnt;
    int spine_state;
    int spine_move_cnt;
    int spine_x;
    int spine_y;
} Level1;
Scene *New_Level1(int label);
void level1_update(Scene *self);
void level1_draw(Scene *self);
void level1_destroy(Scene *self);

#endif
