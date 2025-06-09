#ifndef level3H_INCLUDED
#define level3H_INCLUDED
#include <stdio.h>
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../element/element.h"
#include "../element/charater.h"
#include "camera.h"

#define MAP_WIDTH 80
#define MAP_HEIGHT 46
#define TILE_SIZE 32
/*
   [Set object]
*/
typedef struct _Level3
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;
    int map[MAP_HEIGHT][MAP_WIDTH];
    ALLEGRO_BITMAP *tile_img;
    ALLEGRO_BITMAP *door_img_set;
    Button *back_btn;
    Button *restart_btn;
    int door_cnt;
    int door_state;
    int door_move_cnt;
    Camera camera;

} Level3;
Scene *New_Level3(int label);
void level3_update(Scene *self);
void level3_draw(Scene *self);
void level3_destroy(Scene *self);

#endif
