#ifndef VICYORY_H_INCLUDED
#define VICTORY_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Stage Select object]
*/
typedef struct _Victory
{
    ALLEGRO_BITMAP *background;
    Button *back_btn;
    Button *restart_btn;
    ALLEGRO_SAMPLE *victory_sound;
    ALLEGRO_SAMPLE_INSTANCE *victory_instance;
    bool victory_sound_played;
} Victory;
Scene *New_Victory(int label);
void victory_update(Scene *self);
void victory_draw(Scene *self);
void victory_destroy(Scene *self);
#endif
