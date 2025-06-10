#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "info1.h"
// #define DEMO
/*
   [Stage Select function]
*/
Scene *New_Info1(int label)
{
    info *pDerivedObj = (info *)malloc(sizeof(info));
    Scene *pObj = New_Scene(label);

    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/info1.png");
    

    pDerivedObj->back_btn = New_Button(50.4, 514.9, 91, 91, 0, 0);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");

    pDerivedObj->next_btn = New_Button(1117.4, 514.9, 91, 91, 0, 0);
    pDerivedObj->next_btn->img[0] = al_load_bitmap("assets/image/next_btn_0.png");
    pDerivedObj->next_btn->img[1] = al_load_bitmap("assets/image/next_btn_1.png");
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = info1_update;
    pObj->Draw = info1_draw;
    pObj->Destroy = info1_destroy;
    return pObj;
}
void info1_update(Scene *self)
{
    info *Obj = ((info *)(self->pDerivedObj));
    Button_Update(Obj->back_btn);
    Button_Update(Obj->next_btn);
    
    if(Obj->back_btn->isPress){
        printf("back_btn\n");
        self->scene_end = true;
        window = 0;
    }
    if(Obj->next_btn->isPress){
            self->scene_end = true;
            window = 12;
    }
    return;
}
void info1_draw(Scene *self)
{
    info *Obj = ((info *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->back_btn);
    Draw_Button(Obj->next_btn);


}
void info1_destroy(Scene *self)
{
    info *Obj = ((info *)(self->pDerivedObj));
    
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

