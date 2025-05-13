#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Stage Select object]
*/
typedef struct _Select
{
    ALLEGRO_BITMAP *background;
    Button *lv_btn[4];
    Button *set_btn;
    Button *back_btn;
} Select;
Scene *New_Stage(int label);
void select_update(Scene *self);
void select_draw(Scene *self);
void select_destroy(Scene *self);
#endif
