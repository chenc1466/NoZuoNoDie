#include <allegro5/allegro_primitives.h>
#include "level1_0.h"
#include <stdbool.h>

/*
   [Set function]
*/
Scene *New_Level1_0(int label)
{
    Level1_0 *pDerivedObj = (Level1_0 *)malloc(sizeof(Level1_0));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/shlop.otf", 48, 0);
    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/set.jpg");

    // Back Button
    pDerivedObj->back_btn = New_Button(27, 40, 0, 0, 90, 1);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = level1_0_update;
    pObj->Draw = level1_0_draw;
    pObj->Destroy = level1_0_destroy;
    return pObj;
}
void level1_0_update(Scene *self)
{
    Level1_0 *Obj = ((Level1_0 *)(self->pDerivedObj));
    Button_Update(Obj->back_btn);
        
    if (Obj->back_btn->isPress)
    {
        self->scene_end = true;
        window = 1;
    }


    return;
}
void level1_0_draw(Scene *self)
{
    
    Level1_0 *Obj = ((Level1_0 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->back_btn);

}

void level1_0_destroy(Scene *self)
{
    Level1_0 *Obj = ((Level1_0 *)(self->pDerivedObj));
    
    // Destroy font
    if (Obj->font) {
        al_destroy_font(Obj->font);
        Obj->font = NULL;
    }
    
    // Destroy background
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }

    //Destroy back_btn
    for(int i = 0; i < 2; i++) {
        if (Obj->back_btn->img[i]) {
            al_destroy_bitmap(Obj->back_btn->img[i]);
            Obj->back_btn->img[i] = NULL;
        }
    }
    
    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}
