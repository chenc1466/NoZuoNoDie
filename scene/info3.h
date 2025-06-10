#ifndef INFO3_H_INCLUDED
#define INFO3_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>

typedef struct _info3
{
    ALLEGRO_BITMAP *background;
    Button *back_btn;
} info3;
Scene *New_Info3(int label);
void info3_update(Scene *self);
void info3_draw(Scene *self);
void info3_destroy(Scene *self);
#endif
