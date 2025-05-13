#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED
#include "GAME_ASSERT.h"
#include "global.h"
#include "scene/sceneManager.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>

typedef struct _Game
{
    const char *title;
    ALLEGRO_DISPLAY *display;
    void (*execute)(struct _Game *self);
    void (*game_init)(struct _Game *self);
    bool (*game_update)(struct _Game *self);
    void (*game_draw)(struct _Game *self);
    void (*game_destroy)(struct _Game *self);
} Game;

Game *New_Game();
void execute(Game *self);
void game_init(Game *self);
bool game_update(Game *self);
void game_draw(Game *self);
void game_destroy(Game *self);
void switch_bgm(int bgm_type);

#endif
