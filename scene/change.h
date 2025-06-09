#ifndef CHANGE_H_INCLUDED
#define CHANGE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef struct _Change
{
    ALLEGRO_BITMAP *background;
    Button *black_btn;
    Button *green_btn;
    Button *blue_btn;
    Button *yellow_btn;
    Button *back_btn;

} Change;
Scene* New_Change(int label);
void Change_update(Scene *self);
void Change_draw(Scene *self);
void Change_destroy(Scene *self);

#endif
