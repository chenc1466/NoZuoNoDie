#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "level3.h"
#include "scene.h"
#include "../global.h"
#include "../element/charater.h"

//#define MAP_WIDTH 80
//#define MAP_HEIGHT 46
//#define TILE_SIZE 16

Scene* New_Level3(int label) {
    Level3* pDerivedObj = (Level3*)malloc(sizeof(Level3));
    Scene* pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/lv3.png");
    pDerivedObj->door_img_set = al_load_bitmap("assets/image/door.png");
    //bck_btn
    pDerivedObj->back_btn = New_Button(21, 21, 100, 100, 0, 0);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");
    //restart_btn
    pDerivedObj->restart_btn = New_Button(121, 21, 100, 100, 0, 0);
    pDerivedObj->restart_btn->img[0] = al_load_bitmap("assets/image/rst_btn_0.png");
    pDerivedObj->restart_btn->img[1] = al_load_bitmap("assets/image/rst_btn_1.png");
    // 初始化相機
    init_camera(&pDerivedObj->camera, 1280, 720);

    pObj->pDerivedObj = pDerivedObj;
    // register character
    character_total_state = 3;
    _Register_elements(pObj, New_Character(Character_L));
    // setting derived object function
    pObj->Update = level3_update;
    pObj->Draw = level3_draw;
    pObj->Destroy = level3_destroy;
    return pObj;
}

void level3_update(Scene* self) {
    Level3* Obj = ((Level3*)(self->pDerivedObj));
    if(Obj->door_state == 1)
    {
        Obj->door_move_cnt++;
        if(Obj->door_move_cnt < 80)
            Obj->door_move_cnt++;
        else {
            Obj->door_state = 2;
        }
    }

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
        if(allEle.arr[i]->label == Character_L)
        {
            Character *chara = ((Character *)(allEle.arr[i]->pDerivedObj));
           
            // 更新相機位置以跟隨角色
            float target_x = chara->x - (Obj->camera.width / 2);
            float target_y = chara->y - (Obj->camera.height / 2);
            
            // 限制相機在地圖範圍內
            if (target_x < 0) target_x = 0;
            if (target_y < 0) target_y = 0;
            if (target_x > 2560 - Obj->camera.width) target_x = 2560 - Obj->camera.width;
            if (target_y > 720 - Obj->camera.height) target_y = 720 - Obj->camera.height;
            
            // 更新相機位置
            Obj->camera.x = target_x;
            Obj->camera.y = target_y;
            camera_x = Obj->camera.x;
            camera_y = Obj->camera.y;
            
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
        window = 7;
    }
}

void level3_draw(Scene* self) {
    Level3* Obj = ((Level3*)(self->pDerivedObj));

    // 使用相機偏移繪製背景
    al_draw_scaled_bitmap(Obj->background,
                         0, 0, 2560, 720,  // 源圖片的完整大小
                         -Obj->camera.x, -Obj->camera.y, 2560, 720,  // 目標位置和大小，加上相機偏移
                         0);

    // back button
    Draw_Button(Obj->back_btn);
    // restart button
    Draw_Button(Obj->restart_btn);
    
    // 使用相機偏移繪製門
    double door_x = 1168 + (256-1168) * ((double)Obj->door_move_cnt/80);
    double door_y = 544 + (192-544) * ((double)Obj->door_move_cnt/80);
    al_draw_bitmap_region(Obj->door_img_set, 
                         96 * (int)(Obj->door_cnt/20), 0, 96, 96, 
                         door_x - Obj->camera.x, 
                         door_y - Obj->camera.y, 0);

    // 使用相機偏移繪製角色
    /*
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if(ele->label == Character_L) {
            Character *chara = ((Character *)(ele->pDerivedObj));
            al_draw_bitmap(chara->img[chara->change], 
                          chara->x - Obj->camera.x, 
                          chara->y - Obj->camera.y, 
                          chara->dir ? ALLEGRO_FLIP_HORIZONTAL : 0);
        }
    }
    */
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}

void level3_destroy(Scene* self) {
    Level3* Obj = ((Level3*)(self->pDerivedObj));
    al_destroy_bitmap(Obj->background);
    al_destroy_bitmap(Obj->tile_img);
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
