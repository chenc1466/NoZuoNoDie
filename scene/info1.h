#ifndef INFO1_H_INCLUDED
#define INFO1_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>

typedef struct _info
{
    ALLEGRO_BITMAP *background;
    Button *back_btn;
    Button *next_btn;
} info;
Scene *New_Info1(int label);
void info1_update(Scene *self);
void info1_draw(Scene *self);
void info1_destroy(Scene *self);
#endif
