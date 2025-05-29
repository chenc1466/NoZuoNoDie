#include <allegro5/allegro_primitives.h>
#include "gameover.h"
#include <stdbool.h>
/*
   [Stage Select function]
*/
Scene *New_Gameover(int label)
{
    Gameover *pDerivedObj = (Gameover *)malloc(sizeof(Gameover));
    Scene *pObj = New_Scene(label);

    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/gameover.png");

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function

    // Back Button
    pDerivedObj->back_btn = New_Button(492, 557, 125, 91.4, 0, 0);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_00.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_01.png");
    // Restart Button
    pDerivedObj->restart_btn = New_Button(681, 557, 106.7, 91.4, 0, 0);
    pDerivedObj->restart_btn->img[0] = al_load_bitmap("assets/image/restart_btn_00.png");
    pDerivedObj->restart_btn->img[1] = al_load_bitmap("assets/image/restart_btn_01.png");

    pObj->Update = gameover_update;
    pObj->Draw = gameover_draw;
    pObj->Destroy = gameover_destroy;
    return pObj;
}
void gameover_update(Scene *self)
{
    Gameover*Obj = ((Gameover *)(self->pDerivedObj));
    Button_Update(Obj->restart_btn);
    Button_Update(Obj->back_btn);  
    if (Obj->back_btn->isPress)
    {
        self->scene_end = true;
        window = 1;
    }
    if (Obj->restart_btn->isPress)
    {
        self->scene_end = true;
        window = 3;
    }
    return;
}
void gameover_draw(Scene *self)
{
    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->back_btn);
    Draw_Button(Obj->restart_btn);
}
void gameover_destroy(Scene *self)
{
    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    
    // Destroy background
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }
    // Free Button
    free(Obj->restart_btn);
    Obj->restart_btn = NULL;
    free(Obj->back_btn);
    Obj->back_btn = NULL;

    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}

