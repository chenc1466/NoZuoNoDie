#include <allegro5/allegro_primitives.h>
#include "stageselect.h"
#include <stdbool.h>
/*
   [Stage Select function]
*/
Scene *New_Stage(int label)
{
    Select *pDerivedObj = (Select *)malloc(sizeof(Select));
    Scene *pObj = New_Scene(label);

    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/select.jpg");
    
    // Level 01 Button
    pDerivedObj->lv_btn[0] = New_Button(72, 95, 527, 157, 0, 0);
    pDerivedObj->lv_btn[0]->img[0] = al_load_bitmap("assets/image/lv1_btn_0.png");
    pDerivedObj->lv_btn[0]->img[1] = al_load_bitmap("assets/image/lv1_btn_1.png");
    // Level 02 Button
    pDerivedObj->lv_btn[1] = New_Button(681, 95, 527, 157, 0, 0);
    pDerivedObj->lv_btn[1]->img[0] = al_load_bitmap("assets/image/lv2_btn_0.png");
    pDerivedObj->lv_btn[1]->img[1] = al_load_bitmap("assets/image/lv2_btn_1.png");
    // Level 03 Button
    pDerivedObj->lv_btn[2] = New_Button(72, 297, 527, 157, 0, 0);
    pDerivedObj->lv_btn[2]->img[0] = al_load_bitmap("assets/image/lv3_btn_0.png");
    pDerivedObj->lv_btn[2]->img[1] = al_load_bitmap("assets/image/lv3_btn_1.png");
    // TBD Button
    pDerivedObj->lv_btn[3] = New_Button(681, 297, 527, 157, 0, 0);
    pDerivedObj->lv_btn[3]->img[0] = al_load_bitmap("assets/image/lv4_btn_0.png");
    pDerivedObj->lv_btn[3]->img[1] = al_load_bitmap("assets/image/lv4_btn_1.png");
    // Back Button
    pDerivedObj->back_btn = New_Button(72, 499, 0, 0, 90, 1);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");
    // Setting Button
    pDerivedObj->set_btn = New_Button(1114, 499, 0, 0, 90, 1);
    pDerivedObj->set_btn->img[0] = al_load_bitmap("assets/image/set_btn_0.png");
    pDerivedObj->set_btn->img[1] = al_load_bitmap("assets/image/set_btn_1.png");

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = select_update;
    pObj->Draw = select_draw;
    pObj->Destroy = select_destroy;
    return pObj;
}
void select_update(Scene *self)
{
    Select *Obj = ((Select *)(self->pDerivedObj));
    Button_Update(Obj->set_btn);
    Button_Update(Obj->back_btn);
    for(int i = 0; i < 4; i++)
    {
        Button_Update(Obj->lv_btn[i]);
        if(Obj->lv_btn[0]->isPress){
            self->scene_end = true;
            window = 3;
        }
    }   
    if (Obj->back_btn->isPress)
    {
        self->scene_end = true;
        window = 0;
    }
    if (Obj->set_btn->isPress)
    {
        self->scene_end = true;
        window = 2;
    }
    
    return;
}
void select_draw(Scene *self)
{
    Select *Obj = ((Select *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->set_btn);
    Draw_Button(Obj->back_btn);
    for(int i = 0; i < 4; i++)
        Draw_Button(Obj->lv_btn[i]);
}
void select_destroy(Scene *self)
{
    Select *Obj = ((Select *)(self->pDerivedObj));
    
    // Destroy background
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }
    
    // Destroy button images
    for(int i = 0; i < 2; i++) {
        if (Obj->set_btn->img[i]) {
            al_destroy_bitmap(Obj->set_btn->img[i]);
            Obj->set_btn->img[i] = NULL;
        }
        if (Obj->back_btn->img[i]) {
            al_destroy_bitmap(Obj->back_btn->img[i]);
            Obj->back_btn->img[i] = NULL;
        }
        for(int j = 0; j < 4; j++) {
            if (Obj->lv_btn[j]->img[i]) {
                al_destroy_bitmap(Obj->lv_btn[j]->img[i]);
                Obj->lv_btn[j]->img[i] = NULL;
            }
        }

    }
    
    // Free level buttons
    for(int j = 0; j < 4; j++) {
        free(Obj->lv_btn[j]);
        Obj->lv_btn[j] = NULL;
    }
    
    // Free other buttons
    free(Obj->set_btn);
    Obj->set_btn = NULL;
    free(Obj->back_btn);
    Obj->back_btn = NULL;
    
    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}

