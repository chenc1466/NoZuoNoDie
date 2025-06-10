#ifndef INFO2_H_INCLUDED
#define INFO2_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>

typedef struct _info2
{
    ALLEGRO_BITMAP *background;
    Button *back_btn;
    Button *next_btn;
} info2;
Scene *New_Info2(int label);
void info2_update(Scene *self);
void info2_draw(Scene *self);
void info2_destroy(Scene *self);
#endif
