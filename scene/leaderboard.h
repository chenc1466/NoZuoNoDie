#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>

typedef struct _Leaderboard
{

    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *title_font;
    
    Button *back_btn;
    Button *save_btn;  // 新增保存按鈕
    char names[100][3][100];
    int record_count;
} Leaderboard;

Scene *New_Leaderboard(int label);
void leaderboard_update(Scene *self);
void leaderboard_draw(Scene *self);
void leaderboard_destroy(Scene *self);

#endif 