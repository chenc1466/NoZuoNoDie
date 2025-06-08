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
    pDerivedObj->background = al_load_bitmap("assets/image/lv1.png");
    pDerivedObj->door_img_set = al_load_bitmap("assets/image/door.png");

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

}

void level3_draw(Scene* self) {
    Level3* Obj = ((Level3*)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);

    // draw door //1168,544 -> 256,192
    double door_x = 1168 + (256-1168) * ((double)Obj->door_move_cnt/80);
    double door_y = 544 + (192-544) * ((double)Obj->door_move_cnt/80);
    al_draw_bitmap_region(Obj->door_img_set, 96 * (int)(Obj->door_cnt/20), 0, 96, 96, door_x, door_y, 0);

    // draw character
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
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
    // free the scene objects
    free(Obj);
    free(self);
}
