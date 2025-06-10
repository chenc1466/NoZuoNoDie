#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Stage Select object]
*/
typedef struct _Gameover
{
    ALLEGRO_BITMAP *background;
    Button *back_btn;
    Button *restart_btn;
    ALLEGRO_SAMPLE *gameover_sound;
    ALLEGRO_SAMPLE_INSTANCE *gameover_instance;
    bool gameover_sound_played;   
} Gameover;
Scene *New_Gameover(int label);
void gameover_update(Scene *self);
void gameover_draw(Scene *self);
void gameover_destroy(Scene *self);
#endif
