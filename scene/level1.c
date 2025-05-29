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

#define MAP_WIDTH 80
#define MAP_HEIGHT 46
#define TILE_SIZE 16

Scene* New_Level1(int label) {
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
    // Load map
    FILE* file = fopen("assets/map/lv1_map.csv", "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open map file\n");
        return pObj;
    }

    char line[1024];
    int row = 0;
    while (fgets(line, sizeof(line), file) && row < MAP_HEIGHT) {
        char* token = strtok(line, ",");
        int col = 0;
        while (token && col < MAP_WIDTH) {
            pDerivedObj->map[row][col] = atoi(token);
            token = strtok(NULL, ",");
            col++;
        }
        row++;
    }
    fclose(file);
    pObj->pDerivedObj = pDerivedObj;
    // register character
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
        if(Obj->spine_upsidedown_y < 1360)
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
                self->scene_end = true;
                for(int i=0;i<=10000;i++) {
                    printf(" ");
                    if(i == 10000)  window = 4;
                }
            }
            if(isColliding(chara->x, chara->y, chara->width, chara->height, Obj->spine_upsidedown_x, Obj->spine_upsidedown_y - 48, 128, 64)){
                self->scene_end = true;
                for(int i=0;i<=10000;i++) {
                    printf(" ");
                    if(i == 10000)  window = 4;
                }
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
                    self->scene_end = true;
                    window = 5;
                }
            }else if(Obj->door_cnt > 0)
            {
                Obj->door_cnt--;
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

}

void level1_draw(Scene* self) {
    Level1* Obj = ((Level1*)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);

    // draw door //1168,544 -> 256,192
    double door_x = 1168 + (256-1168) * ((double)Obj->door_move_cnt/80);
    double door_y = 544 + (192-544) * ((double)Obj->door_move_cnt/80);
    al_draw_bitmap_region(Obj->door_img_set, 96 * (int)(Obj->door_cnt/20), 0, 96, 96, door_x, door_y, 0);
    // draw spine
    double spine_x = Obj->spine_x;
    double spine_y = Obj->spine_y - sin((double)Obj->spine_move_cnt/80 * 3.1415926) * 160;
    al_draw_bitmap(Obj->spine_img, spine_x, spine_y, 0);
    // draw upsidedown spine
    double spine_upsidedown_x = Obj->spine_upsidedown_x;
    double spine_upsidedown_y = Obj->spine_upsidedown_y + Obj->spine_upsidedown_move_cnt;
    al_draw_bitmap(Obj->spine_upsidedown_img, spine_upsidedown_x, spine_upsidedown_y, 0);
    Obj->spine_upsidedown_y = spine_upsidedown_y;
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
     // Destroy all elements
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        if (ele && ele->Destroy) {
            ele->Destroy(ele);
        }
    }
    // free the scene objects
    free(Obj);
    free(self);
}
