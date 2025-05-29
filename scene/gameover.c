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
    pObj->Update = gameover_update;
    pObj->Draw = gameover_draw;
    pObj->Destroy = gameover_destroy;
    return pObj;
}
void gameover_update(Scene *self)
{
    
    return;
}
void gameover_draw(Scene *self)
{
    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
}
void gameover_destroy(Scene *self)
{
    Gameover *Obj = ((Gameover *)(self->pDerivedObj));
    
    // Destroy background
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }

    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}

