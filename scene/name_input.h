#ifndef name_input_H_INCLUDED
#define NAME_INPUT_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef struct _NameInput
{
    ALLEGRO_BITMAP *background;
    Button *new_btn;
    Button *save_btn;
    Button *info_btn;
    Button *ctr_btn[4];
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *title_font;
    char name[20];  // 存儲用戶輸入的名字
    int name_length;  // 當前名字長度
    bool is_active;  // 是否正在輸入
    int button_now;
} NameInput;
Scene *New_NameInput(int label);
void name_input_update(Scene *self);
void name_input_draw(Scene *self);
void name_input_destroy(Scene *self);

#endif
