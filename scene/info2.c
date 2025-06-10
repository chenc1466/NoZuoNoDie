#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "info2.h"
// #define DEMO
/*
   [Stage Select function]
*/
Scene *New_Info2(int label)
{
    info2 *pDerivedObj = (info2 *)malloc(sizeof(info2));
    Scene *pObj = New_Scene(label);

    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/info2.png");
    

    pDerivedObj->back_btn = New_Button(50.4, 514.9, 91, 91, 0, 0);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");


    pDerivedObj->next_btn = New_Button(1117.4, 514.9, 91, 91, 0, 0);
    pDerivedObj->next_btn->img[0] = al_load_bitmap("assets/image/next_btn_0.png");
    pDerivedObj->next_btn->img[1] = al_load_bitmap("assets/image/next_btn_1.png");
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = info2_update;
    pObj->Draw = info2_draw;
    pObj->Destroy = info2_destroy;
    return pObj;
}
void info2_update(Scene *self)
{
    info2 *Obj = ((info2 *)(self->pDerivedObj));
    Button_Update(Obj->back_btn);
    Button_Update(Obj->next_btn);
    
    if(Obj->back_btn->isPress){
        self->scene_end = true;
        window = 11;
    }
    if(Obj->next_btn->isPress){
        self->scene_end = true;
        window = 13;
    }
    return;
}
void info2_draw(Scene *self)
{
    info2 *Obj = ((info2 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->back_btn);
    Draw_Button(Obj->next_btn);


}
void info2_destroy(Scene *self)
{
    info2 *Obj = ((info2 *)(self->pDerivedObj));
    
    // Destroy background
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }
    
    // Destroy button images
    for(int i = 0; i < 2; i++) {
        if (Obj->next_btn->img[i]) {
            al_destroy_bitmap(Obj->next_btn->img[i]);
            Obj->next_btn->img[i] = NULL;
        }
        if (Obj->back_btn->img[i]) {
            al_destroy_bitmap(Obj->back_btn->img[i]);
            Obj->back_btn->img[i] = NULL;
        }
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
        if (Obj->next_btn){
        for (int i = 0; i < 2; i++) {
            if (Obj->next_btn->img[i]) {
                al_destroy_bitmap(Obj->next_btn->img[i]);
                Obj->next_btn->img[i] = NULL;
            }
        }
        free(Obj->next_btn);
        Obj->next_btn = NULL;
    }
    
    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}

