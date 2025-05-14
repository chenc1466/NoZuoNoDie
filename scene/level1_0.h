#ifndef level1_0_H_INCLUDED
#define level1_0_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Set object]
*/
typedef struct _Level1_0
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;
    Button *back_btn;

} Level1_0;
Scene *New_Level1_0(int label);
void level1_0_update(Scene *self);
void level1_0_draw(Scene *self);
void level1_0_destroy(Scene *self);

#endif
