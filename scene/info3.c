#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "info3.h"
// #define DEMO
/*
   [Stage Select function]
*/
Scene *New_Info3(int label)
{
    info3 *pDerivedObj = (info3 *)malloc(sizeof(info3));
    Scene *pObj = New_Scene(label);

    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/info3.png");
    

    pDerivedObj->back_btn = New_Button(50.4, 514.9, 91, 91, 0, 0);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = info3_update;
    pObj->Draw = info3_draw;
    pObj->Destroy = info3_destroy;
    return pObj;
}
void info3_update(Scene *self)
{
    info3 *Obj = ((info3 *)(self->pDerivedObj));
    Button_Update(Obj->back_btn);
        if(Obj->back_btn->isPress){
            self->scene_end = true;
            window = 12;
    }
    return;
}
void info3_draw(Scene *self)
{
    info3 *Obj = ((info3 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->back_btn);


}
void info3_destroy(Scene *self)
{
    info3 *Obj = ((info3 *)(self->pDerivedObj));
    
    // Destroy background
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }
    
    // Destroy button images
    for(int i = 0; i < 2; i++) {

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
    
    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}

