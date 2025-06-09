#include <allegro5/allegro_primitives.h>
#include "change.h"
#include <stdbool.h>
#include "../global.h"
/*
   [change function]
*/
Scene* New_Change(int label)
{
    Change* pDerivedObj = (Change *)malloc(sizeof(Change));
    Scene* pObj = New_Scene(label);


    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/change.png");

    pDerivedObj->back_btn = New_Button(21, 21, 91, 91, 0, 0);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");


    // New Game Button
    pDerivedObj->black_btn = New_Button(95.7, 223.9, 224, 320, 0, 0);
    pDerivedObj->black_btn->img[0] = al_load_bitmap("assets/image/black_btn_0.png");
    pDerivedObj->black_btn->img[1] = al_load_bitmap("assets/image/black_btn_1.png");
    // Save/Read Button
    pDerivedObj->green_btn = New_Button(383.7, 223.9, 224, 320, 0, 0);
    pDerivedObj->green_btn->img[0] = al_load_bitmap("assets/image/green_btn_0.png");
    pDerivedObj->green_btn->img[1] = al_load_bitmap("assets/image/green_btn_1.png");
    // Info Button
    pDerivedObj->blue_btn = New_Button(671.7, 223.9, 224, 320, 0, 0);
    pDerivedObj->blue_btn->img[0] = al_load_bitmap("assets/image/blue_btn_0.png");
    pDerivedObj->blue_btn->img[1] = al_load_bitmap("assets/image/blue_btn_1.png");

    pDerivedObj->yellow_btn = New_Button(959.7, 223.9, 224, 320, 0, 0);
    pDerivedObj->yellow_btn->img[0] = al_load_bitmap("assets/image/yellow_btn_0.png");
    pDerivedObj->yellow_btn->img[1] = al_load_bitmap("assets/image/yellow_btn_1.png");

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = Change_update;
    pObj->Draw = Change_draw;
    pObj->Destroy = Change_destroy;
    return pObj;
}
void Change_update(Scene *self)
{
    Change *Obj = ((Change *)(self->pDerivedObj));

    Button_Update(Obj->black_btn);
    Button_Update(Obj->green_btn);
    Button_Update(Obj->blue_btn);
    Button_Update(Obj->yellow_btn);

    if (Obj->black_btn->isPress) {
        current_character = 0;
        self->scene_end = true;
        window = 1; 
    }
    if (Obj->green_btn->isPress) {
        current_character = 1;
        self->scene_end = true;
        window = 1; 
    }
    if (Obj->blue_btn->isPress) {
        current_character = 2;
        self->scene_end = true;
        window = 1;
    }
    if (Obj->yellow_btn->isPress) {
        current_character = 3;
        self->scene_end = true;
        window = 1; 
    }
    Button_Update(Obj->back_btn);
    if (Obj->back_btn->isPress) {
        self->scene_end = true;
        window = 0; 
    }
    
    return;
}

void Change_draw(Scene *self)
{
    Change *Obj = ((Change *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->black_btn);
    Draw_Button(Obj->green_btn);
    Draw_Button(Obj->blue_btn);
    Draw_Button(Obj->yellow_btn);
    Draw_Button(Obj->back_btn);
}
void Change_destroy(Scene *self)
{
    Change *Obj = ((Change *)(self->pDerivedObj));

    // Destroy bitmap resources
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }
    
    // Destroy button images
    for(int i = 0; i < 2; i++) {
        if (Obj->black_btn->img[i]) {
            al_destroy_bitmap(Obj->black_btn->img[i]);
            Obj->black_btn->img[i] = NULL;
        }
        if (Obj->green_btn->img[i]) {
            al_destroy_bitmap(Obj->green_btn->img[i]);
            Obj->green_btn->img[i] = NULL;
        }
        if (Obj->blue_btn->img[i]) {
            al_destroy_bitmap(Obj->blue_btn->img[i]);
            Obj->blue_btn->img[i] = NULL;
        }
        if (Obj->yellow_btn->img[i]) {
            al_destroy_bitmap(Obj->yellow_btn->img[i]);
            Obj->yellow_btn->img[i] = NULL;
        }
        if (Obj->back_btn) {
            for (int i = 0; i < 2; i++) {
                if (Obj->back_btn->img[i]) {
                    al_destroy_bitmap(Obj->back_btn->img[i]);
                    Obj->back_btn->img[i] = NULL;
                }
            }
            free(Obj->back_btn);
            Obj->back_btn = NULL;
        }
    }

    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}
