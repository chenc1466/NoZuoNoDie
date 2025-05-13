#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef struct _Menu
{
    ALLEGRO_BITMAP *background;
    Button *new_btn;
    Button *save_btn;
    Button *info_btn;
} Menu;
Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu_draw(Scene *self);
void menu_destroy(Scene *self);

#endif
