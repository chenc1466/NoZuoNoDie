#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "level1.h"
#include "scene.h"
#include "../global.h"
#include "../element/charater.h"

//#define MAP_WIDTH 80
//#define MAP_HEIGHT 46
//#define TILE_SIZE 16

Scene* New_Level1(int label) {
    level_state = 1;
    Level1* pDerivedObj = (Level1*)malloc(sizeof(Level1));

    Scene* pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/lv1.png");
    pDerivedObj->door_img_set = al_load_bitmap("assets/image/door.png");
    pDerivedObj->spine_img = al_load_bitmap("assets/image/spine.png");
    pDerivedObj->spine_upsidedown_img = al_load_bitmap("assets/image/spine_upsidedown.png");
    pDerivedObj->door_cnt = 0;
    pDerivedObj->door_state = 0;
    pDerivedObj->door_move_cnt = 0;
    // spine 1
    pDerivedObj->spine_state = 0;
    pDerivedObj->spine_move_cnt = 0;
    pDerivedObj->spine_x = 544;
    pDerivedObj->spine_y = 416;
    // spine 2
    pDerivedObj->spine_upsidedown_state = 0;
    pDerivedObj->spine_upsidedown_move_cnt = 0;
    pDerivedObj->spine_upsidedown_x = 1152;
    pDerivedObj->spine_upsidedown_y = -752;
    //bck_btn
    pDerivedObj->back_btn = New_Button(21, 21, 100, 100, 0, 0);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");
    //restart_btn
    pDerivedObj->restart_btn = New_Button(121, 21, 100, 100, 0, 0);
    pDerivedObj->restart_btn->img[0] = al_load_bitmap("assets/image/rst_btn_0.png");
    pDerivedObj->restart_btn->img[1] = al_load_bitmap("assets/image/rst_btn_1.png");

    pObj->pDerivedObj = pDerivedObj;
    // register character
    character_total_state = 1;
    _Register_elements(pObj, New_Character(Character_L));
    // setting derived object function
    pObj->Update = level1_update;
    pObj->Draw = level1_draw;
    pObj->Destroy = level1_destroy;
    return pObj;
}

void level1_update(Scene* self) {
    Level1* Obj = ((Level1*)(self->pDerivedObj));
    if(Obj->door_state == 1)
    {
        Obj->door_move_cnt++;
        if(Obj->door_move_cnt < 80)
            Obj->door_move_cnt++;
        else {
            Obj->door_state = 2;
            Obj->spine_upsidedown_state = 1;
        }
    }
    if(Obj->spine_state == 1){
        if(Obj->spine_move_cnt < 80)
            Obj->spine_move_cnt++;
        else 
            Obj->spine_state = 2;
    }
    if(Obj->spine_upsidedown_state == 1){
        if(Obj->spine_upsidedown_y < 544)
            Obj->spine_upsidedown_move_cnt = 8;
        else {
            Obj->spine_upsidedown_state = 2;
            Obj->spine_upsidedown_move_cnt = 0;
        }
    }
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
        if(allEle.arr[i]->label == Character_L)
        {
            Character *chara = ((Character *)(allEle.arr[i]->pDerivedObj));
            
            if(Obj->spine_state == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 656, 288, 32, 16)){
                Obj->spine_state = 1;
            }

            if(Obj->spine_state == 1 && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->spine_x, Obj->spine_y - 32, 104, 160)){
                dead_cnt = 1;   
                dead_type = 1;
            }
            if(Obj->spine_upsidedown_state == 1 && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->spine_upsidedown_x, Obj->spine_upsidedown_y - 48, 128, 64)){
                dead_cnt = 1;  
                dead_type = 1;
            }

            if(Obj->door_state == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 1216, 64, 96, 96)){
                Obj->door_state = 1;
            }
            if(Obj->door_state == 2 && isColliding(chara->x, chara->y, chara->width, chara->height, 256, 192, 96, 96))
            {
                if(Obj->door_cnt < 80){
                    Obj->door_cnt++;
                }
                else if(Obj->door_cnt == 80){
                    if((finish_level <= 1)){
                       finish_level = 2; 
                    }
                    self->scene_end = true;
                    window = 5;
                    
                }
            }
            else if(Obj->door_cnt > 0)
            {
                Obj->door_cnt--;
            }

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
        window = 3;
    }
}

void level1_draw(Scene* self) {
    Level1* Obj = ((Level1*)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    // draw back button
    Draw_Button(Obj->back_btn);
    // draw restart button  
    Draw_Button(Obj->restart_btn);
    
    // draw door //1168,544 -> 256,192
    double door_x = 1168 + (256-1168) * ((double)Obj->door_move_cnt/80);
    double door_y = 544 + (192-544) * ((double)Obj->door_move_cnt/80);
    al_draw_bitmap_region(Obj->door_img_set, 96 * (int)(Obj->door_cnt/20), 0, 96, 96, door_x, door_y, 0);
    // draw spine
    double spine_x = Obj->spine_x;
    double spine_y = Obj->spine_y - sin((double)Obj->spine_move_cnt/80 * 3.1415926) * 160;
    al_draw_bitmap(Obj->spine_img, spine_x, spine_y, 0);
    // draw upsidedown spine
    double upsidedown_x = Obj->spine_upsidedown_x;
    double upsidedown_y = Obj->spine_upsidedown_y + Obj->spine_upsidedown_move_cnt;
    al_draw_bitmap(Obj->spine_upsidedown_img, upsidedown_x, upsidedown_y, 0);
    Obj->spine_upsidedown_y = upsidedown_y;
    // draw character
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}

void level1_destroy(Scene* self) {
    Level1* Obj = ((Level1*)(self->pDerivedObj));
    al_destroy_bitmap(Obj->background);
    al_destroy_bitmap(Obj->tile_img);
    al_destroy_bitmap(Obj->door_img_set);
    al_destroy_bitmap(Obj->spine_img);
    al_destroy_bitmap(Obj->spine_upsidedown_img);
    for(int i = 0; i < 2; i++) {
        if (Obj->back_btn->img[i]) {
            al_destroy_bitmap(Obj->back_btn->img[i]);
            Obj->back_btn->img[i] = NULL;
        }
        if (Obj->restart_btn->img[i]) {
            al_destroy_bitmap(Obj->restart_btn->img[i]);
            Obj->restart_btn->img[i] = NULL;
        }
    }
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
        Obj->back_btn = NULL;
    }
    // free the scene objects
    free(Obj);
    free(self);
}
