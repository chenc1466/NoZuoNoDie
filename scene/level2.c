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
int cnt[5] = {0, 1, 2, 4, 16};
Scene* New_Level2(int label) {
    Level2* pDerivedObj = (Level2*)malloc(sizeof(Level2));
    Scene* pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/lv2.jpg");
    pDerivedObj->door_img_set = al_load_bitmap("assets/image/door.png");
    pDerivedObj->platform_img_set = al_load_bitmap("assets/image/pfm.jpg");
    pDerivedObj->gear1_img = al_load_bitmap("assets/image/gear.png");
    pDerivedObj->gear2_img = al_load_bitmap("assets/image/gear.png");
    pDerivedObj->gear3_img = al_load_bitmap("assets/image/gear.png");
    pDerivedObj->gear_angle = 0;
    pObj->pDerivedObj = pDerivedObj;
    pDerivedObj->platform_move = 0;
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
    Obj->gear_angle ++;
    if(Obj->gear_angle > 3600)  Obj->gear_angle = 0;
    // door
    if(Obj->door_state == 1)
    {
        Obj->door_move_cnt++;
        if(Obj->door_move_cnt < 80)
            Obj->door_move_cnt++;
        else {
            Obj->door_state = 2;
        }
    }
    if(platform_state == 1)
    {
        if(Obj->platform_move < 80)
            Obj->platform_move++;
    }

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
        if(allEle.arr[i]->label == Character_L)
        {
            Character *chara = ((Character *)(allEle.arr[i]->pDerivedObj));

            //plaftform
            if(platform_state == 0 && isColliding(chara->x, chara->y, chara->width, chara->height, 1040, 540, 96, 112)){
                platform_state = 1;
            }
            else if(platform_state == 1 && isColliding(chara->x, chara->y, chara->width, chara->height, 848, 272, 64, 64)){
                platform_state = 0;
            }
            //character moving

            // door
            /*
            if(isColliding(chara->x, chara->y, chara->width, chara->height, 0, 576, 96, 96)){
                self->scene_end = true;
                    window = 5;
            }
                    */
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

}

void level2_draw(Scene* self) {
    Level2* Obj = ((Level2*)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);

    // draw door //1168,544 -> 256,192
    double door_x = 1168 + (256-1168) * ((double)Obj->door_move_cnt/80);
    double door_y = 544 + (192-544) * ((double)Obj->door_move_cnt/80);
    al_draw_bitmap_region(Obj->door_img_set, 96 * (int)(Obj->door_cnt/20), 0, 96, 96, door_x, door_y, 0);

    // draw gear
    al_draw_rotated_bitmap(Obj->gear1_img, 56, 56, 352 + 56, 624 + 56, Obj->gear_angle/10, 0);
    al_draw_rotated_bitmap(Obj->gear2_img, 56, 56, 938 + 56, 624 + 56, Obj->gear_angle/10, 0);
    al_draw_rotated_bitmap(Obj->gear3_img, 56, 56, 1136 + 56, 624 + 56, Obj->gear_angle/10, 0);

    //platform //1040, 448 -> 1040, 192
    
    double platform_x = 1040;
    double platform_y = 416;
    if(platform_state == 0){
        al_draw_bitmap_region(Obj->platform_img_set, 0, 0, 96, 256, platform_x, platform_y, 0);
    }
    if(platform_state == 1){
        al_draw_bitmap_region(Obj->platform_img_set, 384, 0, 96, 256, platform_x, platform_y, 0);
    }

    
    printf("%d\n", (4 - (int)(Obj->platform_move/20)));
    // draw character
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}

void level2_destroy(Scene* self) {
    Level2* Obj = ((Level2*)(self->pDerivedObj));
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
