#include "charater.h"
#include "../global.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include "../scene/level1.h"
#include "../scene/level2.h"
#include "../scene/level3.h"
#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>

// Global variable for death state
extern int dead_cnt;
int wall_cnt;
int initial_y;
int platform_cnt;
int platform_check[17][4];  // Declare once
int cnt_cnt = 1;
int limit_x = 0;

int cnt[5] = {0, 1, 2, 4, 16};

/* [Character function] */
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);

    // load character image
    if(current_character == 0){
        pDerivedObj->img[0] = al_load_bitmap("assets/image/character/player_black.png");
        pDerivedObj->img[1] = al_load_bitmap("assets/image/character/jump_black.png");
        pDerivedObj->img[2] = al_load_bitmap("assets/image/character/dead_black.png");
        pDerivedObj->img[3] = al_load_bitmap("assets/image/character/bomb_black.png");
        pDerivedObj->img[4] = al_load_bitmap("assets/image/character/transport_black.png");
    }
    else if(current_character == 1){
        pDerivedObj->img[0] = al_load_bitmap("assets/image/character/player_green.png");
        pDerivedObj->img[1] = al_load_bitmap("assets/image/character/jump_green.png");
        pDerivedObj->img[2] = al_load_bitmap("assets/image/character/dead_green.png");
        pDerivedObj->img[3] = al_load_bitmap("assets/image/character/bomb_green.png");
        pDerivedObj->img[4] = al_load_bitmap("assets/image/character/transport_green.png");
    }
    else if(current_character == 2){
        pDerivedObj->img[0] = al_load_bitmap("assets/image/character/player_blue.png");
        pDerivedObj->img[1] = al_load_bitmap("assets/image/character/jump_blue.png");
        pDerivedObj->img[2] = al_load_bitmap("assets/image/character/dead_blue.png");
        pDerivedObj->img[3] = al_load_bitmap("assets/image/character/bomb_blue.png");
        pDerivedObj->img[4] = al_load_bitmap("assets/image/character/transport_blue.png");
    }
    else if(current_character == 3){
        pDerivedObj->img[0] = al_load_bitmap("assets/image/character/player_yellow.png");
        pDerivedObj->img[1] = al_load_bitmap("assets/image/character/jump_yellow.png");
        pDerivedObj->img[2] = al_load_bitmap("assets/image/character/dead_yellow.png");
        pDerivedObj->img[3] = al_load_bitmap("assets/image/character/bomb_yellow.png");
        pDerivedObj->img[4] = al_load_bitmap("assets/image/character/transport_yellow.png");
    }
    pDerivedObj->width = 64;
    pDerivedObj->height = 112;
    pDerivedObj->chara_cnt = 0;
    pDerivedObj->change = 0;
    pDerivedObj->move_step = 0;

    // load attack sound
    pDerivedObj->jump_sound = al_load_sample("assets/sound/jump.wav");


    // init position and hitbox
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);

    pDerivedObj->dir = false;
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pDerivedObj->velocity_y = 0;
    pDerivedObj->gravity = 0.3f;
    pDerivedObj->jump_force = -10.0f;
    pDerivedObj->is_jumping = false;


    switch (level_state) {
        case 1: {
            int temp[7][4] = {
                {912, 576, 160, 64},
                {1072, 192, 80, 384},
                {192, 288, 224, 64},
                {480, 160, 144, 64},
                {528, 400, 208, 64},
                {752, 112, 208, 64},
                {848, 464, 144, 64}
            };
            platform_cnt = 7;
            wall_cnt = 2;
            initial_y = 640;
            limit_x = 1280;
            memcpy(platform_check, temp, sizeof(temp));
            break;
        }
        case 2: {
            int temp[8][4] = {
                {96, 0, 96, 720},
                {624, 576, 128, 96},
                {352, 208, 224, 64},
                {656, 336, 256, 64},
                {752, 112, 240, 64},
                {1152, 208, 96, 96},
                {1040, 416, 96, 32}, 
                {1040, 656, 96, 32}, 
            };
            pDerivedObj->x = 192;
            platform_cnt = 8;
            wall_cnt = 2;
            initial_y = 672;
            limit_x = 1280;
            memcpy(platform_check, temp, sizeof(temp));
            break;
        }
        case 3: {

            int temp[14][4] = {
                {0, 480, 224, 240},
                {336, 480, 432, 240},
                {992, 480, 656, 240},
                {1760, 480, 288, 240},
                {2240, 480, 320, 240},
                {1968, 448, 80, 32},
                {768, 720, 224, 32},
                {2048, 720, 192, 32},
                {848, 192, 48, 32},
                {720, 336, 208, 64},
                {928, 112, 208, 80},
                {2096, 384, 112, 48},
                {224, 480, 112, 32},
                {1648, 480, 112, 32}
            };
            platform_cnt = 15;
            wall_cnt = 8;
            initial_y = 864;
            limit_x = 2560;
            memcpy(platform_check, temp, sizeof(temp));
            break;
        }
        default:
            break;
    }
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;

    return pObj;
}

void Character_update(Elements *self)
{
    Character *chara = ((Character *)(self->pDerivedObj));

    // Check for death state
    if (dead_cnt) {
        chara->state = DEAD;
    }
    int origin_x = chara->x;
    int origin_y = chara->y;
    if (chara->state == STOP)
    {
        chara->chara_cnt = 0;
        if ((key_state[key_used[2]] || key_state[ALLEGRO_KEY_W]) && !chara->is_jumping)
        {
            chara->velocity_y = chara->jump_force;
            chara->is_jumping = true;
            chara->change = 1;
                        if(chara->jump_sound){
                chara->jump_instance = al_create_sample_instance(chara->jump_sound);
                al_attach_sample_instance_to_mixer(chara->jump_instance, al_get_default_mixer());
                al_play_sample_instance(chara->jump_instance);
                chara->jump_instance = chara->jump_instance;

            }
        }

        if (key_state[key_used[0]] || key_state[ALLEGRO_KEY_A]) // left
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else if (key_state[key_used[1]] || key_state[ALLEGRO_KEY_D]) // right
        {
            chara->dir = true;
            chara->state = MOVE;
        }
    }
    else if (chara->state == MOVE)
    {
        int move_step = 5;
        if(chara->chara_cnt < 15)   
            chara->chara_cnt++;

        if(chara->chara_cnt == 15) {
            chara->move_step = !chara->move_step;
            chara->chara_cnt = 0;
        }
        
        if ((key_state[key_used[2]] || key_state[ALLEGRO_KEY_W]) && !chara->is_jumping)
        {
            chara->velocity_y = chara->jump_force;
            chara->is_jumping = true;
            chara->state = MOVE;
            if(chara->jump_sound){
                chara->jump_instance = al_create_sample_instance(chara->jump_sound);
                al_attach_sample_instance_to_mixer(chara->jump_instance, al_get_default_mixer());
                al_play_sample_instance(chara->jump_instance);
                chara->jump_instance = chara->jump_instance;

            }
        }

        if (key_state[key_used[0]] || key_state[ALLEGRO_KEY_A]) // left
        {
            chara->dir = false;
            chara->x -= move_step;
            chara->state = MOVE;
        }
        else if (key_state[key_used[1]] || key_state[ALLEGRO_KEY_D]) // right
        {
            chara->dir = true;
            chara->x += move_step;
            chara->state = MOVE;
        }
        if(!(key_state[key_used[0]] || key_state[ALLEGRO_KEY_A] ||
           key_state[key_used[1]] || key_state[ALLEGRO_KEY_D] ||
           key_state[key_used[2]] || key_state[ALLEGRO_KEY_W])) {
            chara->state = STOP;
            chara->chara_cnt = 0;
        }
    }

    if(chara->x < 0)
        chara->x = 0;
    if(chara->x+chara->width > limit_x)
        chara->x = limit_x - chara->width;
    // 處理跳躍 & 重力
    chara->velocity_y += chara->gravity;
    chara->y += chara->velocity_y;
    platform_check[12][1] = canyon1_y;
    platform_check[13][1] = canyon2_y;
    for (int i = 0; i < platform_cnt; i++) {
        int px = platform_check[i][0];  // 平台 x
        int py = platform_check[i][1];  // 平台 y
        int pw = platform_check[i][2];  // 平台寬度
        int ph = platform_check[i][3];  // 平台高度

        bool overlapX = (chara->x + chara->width > px) && (chara->x < px + pw);
        bool fallingFromAbove = (origin_y + chara->height <= py);
        bool hasLanded = (chara->y + chara->height >= py);

        if (overlapX && fallingFromAbove && hasLanded) {
            chara->y = py - chara->height;   // 放在平台上
            chara->is_jumping = false;       // 停止跳躍
            chara->velocity_y = 0;           // 垂直速度歸零
            chara->change = 0;
            break;
        }
    }        
    


    for (int i = 0; i < wall_cnt; i++) {
        int px = platform_check[i][0];
        int py = platform_check[i][1];
        int pw = platform_check[i][2];
        int ph = platform_check[i][3];

        if (isColliding(chara->x, chara->y, chara->width, chara->height,
                        px, py, pw, ph)) {
            chara->x = origin_x;
            break;
        }
    }

    if(chara->y > initial_y - chara->height){
        chara->y = initial_y - chara->height;
        chara->is_jumping = false;
        chara->velocity_y = 0;
        chara->change = 0;
    }
}

void Character_draw(Elements *self)
{
    Character *chara = ((Character *)(self->pDerivedObj));

    // printf("chara->x: %d, chara->y: %d ", chara->x, chara->y);
    // printf("camera_x: %d, camera_y: %d\n", camera_x, camera_y);

    if(portal_appear == 2){
        al_draw_bitmap_region(chara->img[4], 64 * (portal_cnt/20), 0, 64, 112, chara->x - camera_x, chara->y - camera_y, 1);
    }
    else if(portal_appear == 3){
        chara->x = 16;
        chara->y = 16;
        al_draw_bitmap_region(chara->img[0], 0, 0, 64, 112, chara->x - camera_x, chara->y - camera_y, 1);
        portal_appear = 4;
    }
    
    else if (chara->state == STOP){
        if(chara->change == 0){
            al_draw_bitmap_region(chara->img[0], 0, 0, 64, 112, chara->x - camera_x, chara->y - camera_y, (chara->dir ? 0 : ALLEGRO_FLIP_HORIZONTAL));
        }
        else if(chara->change == 1){
            al_draw_bitmap(chara->img[1], chara->x - camera_x, chara->y - camera_y, (chara->dir ? 0 : ALLEGRO_FLIP_HORIZONTAL));
        }
    }
   
    else if (chara->state == MOVE){
         if(chara->move_step == 0){
            al_draw_bitmap_region(chara->img[0], 64, 0, 64, 112, chara->x - camera_x, chara->y - camera_y, (chara->dir ? 0 : ALLEGRO_FLIP_HORIZONTAL));
        }
        else if(chara->move_step == 1){
            al_draw_bitmap_region(chara->img[0], 128, 0, 64, 112, chara->x - camera_x, chara->y - camera_y, (chara->dir ? 0 : ALLEGRO_FLIP_HORIZONTAL));
        }
    }

    else if(chara->state == DEAD){
        if(dead_type == 4){
            al_draw_bitmap_region(chara->img[3], 64 * (bomb_cnt/20), 0, 64, 112, chara->x - camera_x, chara->y - camera_y, 1);
        }
        else{
            al_draw_bitmap(chara->img[2], chara->x - camera_x, chara->y - camera_y, 1);
        }
        
        if(dead_type == 4 && bomb_cnt >= 80){
            dead_cnt = 2;
        }
        else if(dead_type != 4){
            dead_cnt = 2;
        }

    }

}

void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img[0]);
    al_destroy_bitmap(Obj->img[1]);
    al_destroy_bitmap(Obj->img[2]);
    al_destroy_bitmap(Obj->img[3]);
    if(Obj->jump_sound){
        al_destroy_sample(Obj->jump_sound);
        Obj->jump_sound = NULL;
    }
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
void Character_interact(Elements *self, Elements *target){}

void _Character_update_position(Elements *self, int dx, int dy)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

