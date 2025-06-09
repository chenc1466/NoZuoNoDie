#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "level2.h"
#include "scene.h"
#include "../global.h"
#include "../element/charater.h"

//#define MAP_WIDTH 80
//#define MAP_HEIGHT 46
//#define TILE_SIZE 16
Scene* New_Level2(int label) {
    level_state = 2;
    Level2* pDerivedObj = (Level2*)malloc(sizeof(Level2));
    Scene* pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/lv2.png");
    pDerivedObj->door_img_set = al_load_bitmap("assets/image/door.png");
    pDerivedObj->platform_img_set = al_load_bitmap("assets/image/pfm.jpg");
    //spine
    pDerivedObj->spine_upsidedown_img = al_load_bitmap("assets/image/spine_upsidedown.png");
    pDerivedObj->spine_upsidedown_x = 752;
    pDerivedObj->spine_upsidedown_y = 384;
    pDerivedObj->spine_upsidedown_state = 0;
    pDerivedObj->spine_upsidedown_move_cnt = 0;
    //portal
    pDerivedObj->portal1_img = al_load_bitmap("assets/image/portal.png");
    pDerivedObj->portal2_img = al_load_bitmap("assets/image/portal.png");
    pDerivedObj->portal_appear = 0;
    //gear
    pDerivedObj->gear1_img = al_load_bitmap("assets/image/gear.png");
    pDerivedObj->gear2_img = al_load_bitmap("assets/image/gear.png");
    pDerivedObj->gear3_img = al_load_bitmap("assets/image/gear.png");
    pDerivedObj->gear_angle = 0;
    pDerivedObj->gear1_x = 352;
    pDerivedObj->gear1_y = 624;
    pDerivedObj->gear2_x = 938;
    pDerivedObj->gear2_y = 624;
    pDerivedObj->gear3_x = 1136;
    pDerivedObj->gear3_y = 624;
    pObj->pDerivedObj = pDerivedObj;
    pDerivedObj->platform_move = 0;
    platform_state = 0;
    //bck_btn
    pDerivedObj->back_btn = New_Button(21, 21, 100, 100, 0, 0);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");
    //restart_btn
    pDerivedObj->restart_btn = New_Button(121, 21, 100, 100, 0, 0);
    pDerivedObj->restart_btn->img[0] = al_load_bitmap("assets/image/rst_btn_0.png");
    pDerivedObj->restart_btn->img[1] = al_load_bitmap("assets/image/rst_btn_1.png");
    // register character
    character_total_state = 2;
    _Register_elements(pObj, New_Character(Character_L));
    // setting derived object function
    pObj->Update = level2_update;
    pObj->Draw = level2_draw;
    pObj->Destroy = level2_destroy;
    return pObj;
}

void level2_update(Scene* self) {
    Level2* Obj = ((Level2*)(self->pDerivedObj));
    // gear
    Obj->gear_angle++;
    if(Obj->gear_angle > 3600)  Obj->gear_angle = 0;


    // Spine movement
    if(Obj->spine_upsidedown_state == 1) {
        if(Obj->spine_upsidedown_y < 640)
            Obj->spine_upsidedown_move_cnt = 1;
        else {
            Obj->spine_upsidedown_state = 2;
            Obj->spine_upsidedown_move_cnt = 0;
        }
    }

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        allEle.arr[i]->Update(allEle.arr[i]);
        if(allEle.arr[i]->label == Character_L) {
            Character *chara = ((Character *)(allEle.arr[i]->pDerivedObj));
            
            // Platform collision and movement
            if(isColliding(chara->x, chara->y, chara->width, chara->height, 1088, 640, 48, 32)) {
                // Character is on platform
                chara->y = 304;

                // Start platform movement when character lands
                if(platform_state == 0) {
                    platform_state = 1;
                }
            }
            
            if(platform_state == 1){
                if(!isColliding(chara->x, chara->y, chara->width, chara->height, 1040, 210, 96, 128)){
                    platform_state = 0;
                }
            }
            // door
            if(isColliding(chara->x, chara->y, chara->width, chara->height, 0, 576, 96, 96))
            {
                if(Obj->door_cnt < 80){
                    Obj->door_cnt++;
                }
                else if(Obj->door_cnt == 80){
                    level_state = 3;
                    self->scene_end = true;
                    window = 5;
                }
            }
            else if(Obj->door_cnt > 0)
            {
                Obj->door_cnt--;
            }
            //spine
            if(Obj->spine_upsidedown_state == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 784, 640, 32, 16)){
                Obj->spine_upsidedown_state = 1;
                Obj->portal_appear = 1;
            }
            else if(Obj->spine_upsidedown_state == 2 && isColliding(chara->x, chara->y, chara->width, chara->height, 752, 640, 128, 32)){
                dead_cnt = 1;  
                dead_type = 1;
                Obj->spine_upsidedown_state = 3;  
            }
            //gear
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->gear1_x, Obj->gear1_y + 16, 112, 112)
                             && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->gear1_x + 16, Obj->gear1_y, 80, 112)){
                dead_cnt = 1;  
                dead_type = 2;              
            }
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->gear2_x, Obj->gear2_y + 16, 112, 112)
                             && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->gear2_x + 16, Obj->gear2_y, 80, 112)){
                dead_cnt = 1;
                dead_type = 2;
            }
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->gear3_x, Obj->gear3_y + 16, 112, 112)
                             && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->gear3_x + 16, Obj->gear3_y, 80, 112)){
                dead_cnt = 1;
                dead_type = 2;
            }
            //transform
            if(isColliding(chara->x, chara->y, chara->width, chara->height, 1024, 96, 96, 32)){
                chara->x = 0;
                chara->y = 0;
            }
            //dead
            if(dead_cnt == 2){
                dead_cnt = 0;
                self->scene_end = true;
                window = 4;
            }
        }
    }
    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
    // back button
    Button_Update(Obj->back_btn);
    if (Obj->back_btn->isPress)
    {
        self->scene_end = true;
        window = 1;
    }
    // restart button
    Button_Update(Obj->restart_btn);
    if (Obj->restart_btn->isPress)
    {
        self->scene_end = true;
        window = 6;
    }
}

void level2_draw(Scene* self) {
    Level2* Obj = ((Level2*)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    

    // draw door
    al_draw_bitmap_region(Obj->door_img_set, 96 * (int)(Obj->door_cnt/20), 0, 96, 96, 0, 576, 0);

    // draw portal
    if(Obj->portal_appear == 1){
        al_draw_bitmap(Obj->portal1_img, 16, 32, 0);
        al_draw_bitmap(Obj->portal2_img, 1024, 96, 0);
    }

    // back button
    Draw_Button(Obj->back_btn);
    // restart button
    Draw_Button(Obj->restart_btn);

    // draw upsidedown spine
    Obj->spine_upsidedown_y = Obj->spine_upsidedown_y + Obj->spine_upsidedown_move_cnt;
    al_draw_bitmap(Obj->spine_upsidedown_img, Obj->spine_upsidedown_x, Obj->spine_upsidedown_y, 0);
    
    // draw gear
    al_draw_rotated_bitmap(Obj->gear1_img, 56, 56, 352 + 56, 624 + 56, Obj->gear_angle/10, 0);
    al_draw_rotated_bitmap(Obj->gear2_img, 56, 56, 938 + 56, 624 + 56, Obj->gear_angle/10, 0);
    al_draw_rotated_bitmap(Obj->gear3_img, 56, 56, 1136 + 56, 624 + 56, Obj->gear_angle/10, 0);

    // draw platform

    al_draw_bitmap_region(Obj->platform_img_set, 0, 0, 96, 256, 1040, 416, 0);
    
    if(platform_state == 1 ) {
        al_draw_bitmap_region(Obj->platform_img_set, 384, 0, 96, 256, 1040, 416, 0);
    }
    
    // draw character
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}

void level2_destroy(Scene* self) {
    Level2* Obj = ((Level2*)(self->pDerivedObj));
    al_destroy_bitmap(Obj->background);
    al_destroy_bitmap(Obj->door_img_set);
    al_destroy_bitmap(Obj->gear1_img);
    al_destroy_bitmap(Obj->gear2_img);
    al_destroy_bitmap(Obj->gear3_img);
    al_destroy_bitmap(Obj->platform_img_set);
     // Destroy all elements
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        if (ele && ele->Destroy) {
            ele->Destroy(ele);
        }
    }
    if (Obj->restart_btn){
        for (int i = 0; i < 2; i++) {
            if (Obj->restart_btn->img[i]) {
                al_destroy_bitmap(Obj->restart_btn->img[i]);
                Obj->restart_btn->img[i] = NULL;
            }
        }
        free(Obj->restart_btn);
        Obj->restart_btn = NULL;
    }
    if (Obj->back_btn){
        for (int i = 0; i < 2; i++) {
            if (Obj->back_btn->img[i]) {
                al_destroy_bitmap(Obj->back_btn->img[i]);
                Obj->back_btn->img[i] = NULL;
            }
        }
        free(Obj->back_btn);
        Obj->back_btn = NULL;
    }
    // free the scene objects
    free(Obj);
    free(self);
}
