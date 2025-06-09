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
    level_state = 3;
    Level3* pDerivedObj = (Level3*)malloc(sizeof(Level3));
    Scene* pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/lv3.png");
    pDerivedObj->door_img_set = al_load_bitmap("assets/image/door.png");
    pDerivedObj->platform_img_set = al_load_bitmap("assets/image/pfm.jpg");
    pDerivedObj->door_cnt = 0;
    pDerivedObj->door_state = 0;
    //spine
    pDerivedObj->spine1_img = al_load_bitmap("assets/image/spine2.png");
    pDerivedObj->spine2_img = al_load_bitmap("assets/image/spine3.png");
    pDerivedObj->spine3_img = al_load_bitmap("assets/image/spine4.png");
    pDerivedObj->spine4_img = al_load_bitmap("assets/image/spine4.png");
    pDerivedObj->spine5_img = al_load_bitmap("assets/image/spine4.png");
    pDerivedObj->spine_state = 0;
    pDerivedObj->spine_move_cnt = 0;
    pDerivedObj->spine_x = 2096;
    pDerivedObj->spine_y = 384;
    //button
    pDerivedObj->button1_img = al_load_bitmap("assets/image/button0.png");
    pDerivedObj->button1_pressed_img = al_load_bitmap("assets/image/button1.png");
    pDerivedObj->button2_img = al_load_bitmap("assets/image/button0.png");
    pDerivedObj->button2_pressed_img = al_load_bitmap("assets/image/button1.png");
    pDerivedObj->button3_img = al_load_bitmap("assets/image/button0.png");
    pDerivedObj->button3_pressed_img = al_load_bitmap("assets/image/button1.png");
    pDerivedObj->button1_state = 0;
    pDerivedObj->button2_state = 0;
    pDerivedObj->button3_state = 0;
    bomb_cnt = 0;
    //canyon
    pDerivedObj->canyon1_img = al_load_bitmap("assets/image/canyon.png");
    pDerivedObj->canyon2_img = al_load_bitmap("assets/image/canyon.png");
    pDerivedObj->canyon1_state = 0;
    pDerivedObj->canyon2_state = 0;
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
    canyon1_y = 480;
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
   if(Obj->spine_state == 1){
        if(Obj->spine_move_cnt < 80)
            Obj->spine_move_cnt++;
        else 
            Obj->spine_state = 2;
    }
    if(dead_cnt == 1 && dead_type == 4){
        bomb_cnt++;
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

            // spine
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 768, 688, 224, 32))
            {
                dead_cnt = 1;
                dead_type = 1;
            }
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 2048, 688, 192, 32))
            {
                dead_cnt = 1;
                dead_type = 1;
            }
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 224, 704, 96, 64))
            {
                dead_cnt = 1;
                dead_type = 3;
            }
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 1648, 704, 32, 64))
            {
                dead_cnt = 1;
                dead_type = 3;
            }
            if(Obj->spine_state == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 2048, 224, 32, 16)){
                Obj->spine_state = 1;
            }
            if(Obj->spine_state == 1 && isColliding(chara->x, chara->y, chara->width, chara->height, Obj->spine_x, Obj->spine_y - 16, 112, 160)){
                dead_cnt = 1;   
                dead_type = 1;
            }
            // button1
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 1104, 80, 16, 32)){
                Obj->button1_state = 1;
                dead_cnt = 1;
                dead_type = 4;
            }
            // button2
            if(isColliding(chara->x, chara->y, chara->width, chara->height, 1024, 448, 32, 32)){
                Obj->button2_state = 1;
                Obj->door_state = 1;
            }
            else{
                Obj->button2_state = 0;
            }
            // button3
            if(dead_cnt == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 1824, 448, 8, 32)){
                Obj->button3_state = 1;
                dead_cnt = 1;
                dead_type = 4;
            }
            // door
            if(Obj->door_state == 1 && isColliding(chara->x, chara->y, chara->width, chara->height, 1296, 384, 96, 96))
            {
                Obj->door_state = 2;
            }
            if(Obj->door_state == 2 && isColliding(chara->x, chara->y, chara->width, chara->height, 2464, 384, 96, 96))
            {
                if(Obj->door_cnt < 80){
                    Obj->door_cnt++;
                }
                else if(Obj->door_cnt == 80){
                    finish_level = 2;
                    self->scene_end = true;
                    window = 5;
                }
            }
            else if(Obj->door_cnt > 0)
            {
                Obj->door_cnt--;
            }
            //printf("%d\n", chara->y);
            //platform
            if(isColliding(chara->x, chara->y, chara->width, chara->height, 880, 208, 32, 32)) {
                // Character is on platform
                chara->y = 80;

                // Start platform movement when character lands
                if(platform_state == 0) {
                    platform_state = 1;
                }
            }
            if(platform_state == 1){
                if(!isColliding(chara->x, chara->y, chara->width, chara->height, 816, 16, 96, 128)){
                    platform_state = 0;
                }
            }
            //canyon1
            if(isColliding(chara->x, chara->y, chara->width, chara->height, 208, 464, 32, 32)) {
                // Start platform movement when character lands
                canyon1_y = 720;
                if(Obj->canyon1_state == 0) {
                    Obj->canyon1_state = 1;
                }
            }

            //canyon2
            if(isColliding(chara->x, chara->y, chara->width, chara->height, 1632, 448, 32, 32)) {
                // Start platform movement when character lands
                canyon2_y = 720;
                if(Obj->canyon2_state == 0) {
                    Obj->canyon2_state = 1;
                }
            }

            if(dead_cnt == 2){
                //printf("dead\n");
                dead_cnt = 0;
                self->scene_end = true;
                window = 4;
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
}

void level3_draw(Scene* self) {
    Level3* Obj = ((Level3*)(self->pDerivedObj));

    // 使用相機偏移繪製背景
    al_draw_scaled_bitmap(Obj->background,
                         0, 0, 2560, 720,  // 源圖片的完整大小
                         -Obj->camera.x, -Obj->camera.y, 2560, 720,  // 目標位置和大小，加上相機偏移
                         0);
    
    // draw button1
    if(Obj->button1_state == 0){
        al_draw_bitmap(Obj->button1_img, 1072 - Obj->camera.x, 80 - Obj->camera.y, 0);
    }
    else{
        al_draw_bitmap(Obj->button1_pressed_img, 1072 - Obj->camera.x, 96 - Obj->camera.y, 0);
    }
    // draw button2
    if(Obj->button2_state == 0){
        al_draw_bitmap(Obj->button2_img, 1008 - Obj->camera.x, 448 - Obj->camera.y, 0);
    }
    else{
        al_draw_bitmap(Obj->button2_pressed_img, 1008 - Obj->camera.x, 464 - Obj->camera.y, 0);
    }
    // draw button3
    if(Obj->button3_state == 0){
        al_draw_bitmap(Obj->button3_img, 1792 - Obj->camera.x, 448 - Obj->camera.y, 0);
    }
    else{
        al_draw_bitmap(Obj->button3_pressed_img, 1792 - Obj->camera.x, 464 - Obj->camera.y, 0);
    }

    // draw spine
    al_draw_bitmap(Obj->spine1_img, 768 - Obj->camera.x, 688 - Obj->camera.y, 0);
    al_draw_bitmap(Obj->spine2_img, 2048 - Obj->camera.x, 688 - Obj->camera.y, 0);
    al_draw_bitmap(Obj->spine4_img, 224 - Obj->camera.x, 720 - Obj->camera.y, 0);
    al_draw_bitmap(Obj->spine5_img, 1648 - Obj->camera.x, 720 - Obj->camera.y, 0);
    // draw spine
    double spine_x = Obj->spine_x - Obj->camera.x;
    double spine_y = Obj->spine_y - Obj->camera.y - sin((double)Obj->spine_move_cnt/80 * 3.1415926) * 160;
    al_draw_bitmap(Obj->spine3_img, spine_x, spine_y, 0);
    // back button
    Draw_Button(Obj->back_btn);
    // restart button
    Draw_Button(Obj->restart_btn);
    
    // 使用相機偏移繪製門 2560,384 -> 1296,384 -> 2464,384
    if(Obj->door_state == 0){
        al_draw_bitmap_region(Obj->door_img_set, 
                            0, 0, 96, 96, 
                            2560 - Obj->camera.x, 
                            384 - Obj->camera.y, 0);
    }
    else if(Obj->door_state == 1){
        al_draw_bitmap_region(Obj->door_img_set, 
                            0, 0, 96, 96, 
                            1296 - Obj->camera.x, 
                            384 - Obj->camera.y, 0);
    }
    else if(Obj->door_state == 2){
        al_draw_bitmap_region(Obj->door_img_set, 
                            96 * (int)(Obj->door_cnt/20), 0, 96, 96, 
                            2464 - Obj->camera.x, 
                            384 - Obj->camera.y, 0);
    }
    // draw platform
    al_draw_bitmap_region(Obj->platform_img_set, 0, 0, 96, 256, 832 - Obj->camera.x, 144 - Obj->camera.y, 0);
    if(platform_state == 1){
        al_draw_bitmap_region(Obj->platform_img_set, 384, 0, 96, 160, 832 - Obj->camera.x, 192 - Obj->camera.y, 0);
    }
    // draw canyon1
    if(Obj->canyon1_state == 0){
        al_draw_bitmap_region(Obj->canyon1_img, 0, 0, 112, 240, 224 - Obj->camera.x, 480 - Obj->camera.y, 0);
    }
    else if(Obj->canyon1_state == 1){
        al_draw_bitmap_region(Obj->canyon1_img, 112, 0, 112, 240, 224 - Obj->camera.x, 480 - Obj->camera.y, 0);
    }
    // draw canyon2
    if(Obj->canyon2_state == 0){
        al_draw_bitmap_region(Obj->canyon2_img, 0, 0, 112, 240, 1648 - Obj->camera.x, 480 - Obj->camera.y, 0);
    }
    else if(Obj->canyon2_state == 1){
        al_draw_bitmap_region(Obj->canyon2_img, 112, 0, 112, 240, 1648 - Obj->camera.x, 480 - Obj->camera.y, 0);
    }
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
    al_destroy_bitmap(Obj->door_img_set);
    al_destroy_bitmap(Obj->platform_img_set);
    al_destroy_bitmap(Obj->spine1_img);
    al_destroy_bitmap(Obj->spine2_img);
    al_destroy_bitmap(Obj->spine3_img);
    al_destroy_bitmap(Obj->spine4_img);
    al_destroy_bitmap(Obj->spine5_img);
    al_destroy_bitmap(Obj->button1_img);
    al_destroy_bitmap(Obj->button1_pressed_img);
    al_destroy_bitmap(Obj->button2_img);
    al_destroy_bitmap(Obj->button2_pressed_img);
    al_destroy_bitmap(Obj->button3_img);
    al_destroy_bitmap(Obj->button3_pressed_img);
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
        free(Obj->back_btn);
        Obj->back_btn = NULL;
    }
    // free the scene objects
    free(Obj);
    free(self);
}
