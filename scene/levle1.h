#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Set object]
*/
typedef struct _Set
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;
    Button *back_btn;
    Button *bgm1_btn;
    Button *bgm2_btn;
    Button *vol1_btn;
    Button *vol2_btn;
} Set;
Scene *New_Set(int label);
void set_update(Scene *self);
void set_draw(Scene *self);
void set_destroy(Scene *self);

#endif
