#include "charater.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>


int platform_check[7][4] = {{912, 576, 160, 64},
                        {1072, 192, 80, 384},
                        {192, 288, 224, 64},
                        {480, 160, 144, 64},
                        {528, 400, 208, 64},
                        {752, 112, 208, 64},
                        {848, 464, 144, 64}
                        };

/* [Character function] */
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);

    // load character image
    pDerivedObj->img = al_load_bitmap("assets/image/player.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    // load attack sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

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
    Level1 *level = (Level1 *)(scene->pDerivedObj);
    int tile_size = 32; // 請根據你的地圖實際 tile size 調整

    int origin_x = chara->x;
    int origin_y = chara->y;

    if (chara->state == STOP)
    {
        if ((key_state[key_used[2]] || key_state[ALLEGRO_KEY_W]) && !chara->is_jumping)
        {
            chara->velocity_y = chara->jump_force;
            chara->is_jumping = true;
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
        if (key_state[key_used[0]] || key_state[ALLEGRO_KEY_A]) // left
        {
            chara->dir = false;
            chara->x -= move_step;
        }
        else if (key_state[key_used[1]] || key_state[ALLEGRO_KEY_D]) // right
        {
            chara->dir = true;
            chara->x += move_step;
        }
        chara->state = STOP;
    }
    if(chara->x < 0)
        chara->x = 0;
    if(chara->x+chara->width > 1280)
        chara->x = 1280 - chara->width;
    // 處理跳躍 & 重力
    chara->velocity_y += chara->gravity;
    chara->y += chara->velocity_y;

    for (int i = 0; i < 7; i++) {
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
            break;
        }
    }

    for (int i = 0; i < 2; i++) {
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

    if(chara->y > 640 - chara->height){
        chara->y =  640 - chara->height;
        chara->is_jumping = false;
        chara->velocity_y = 0;
    }
}

void Character_draw(Elements *self)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = chara->img;
    if (frame)
        al_draw_bitmap(frame, chara->x, chara->y, (chara->dir ? ALLEGRO_FLIP_HORIZONTAL : 0));
}

void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    al_destroy_bitmap(Obj->img);
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

