#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
/*
   [Menu function]
*/
Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);

    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/menu.jpg");

    // New Game Button
    pDerivedObj->new_btn = New_Button(527, 370, 263, 120, 0, 0);
    pDerivedObj->new_btn->img[0] = al_load_bitmap("assets/image/new_btn_0.png");
    pDerivedObj->new_btn->img[1] = al_load_bitmap("assets/image/new_btn_1.png");
    // Save/Read Button
    pDerivedObj->save_btn = New_Button(506, 500, 304, 120, 0, 0);
    pDerivedObj->save_btn->img[0] = al_load_bitmap("assets/image/save_btn_0.png");
    pDerivedObj->save_btn->img[1] = al_load_bitmap("assets/image/save_btn_1.png");
    // Info Button
    pDerivedObj->info_btn = New_Button(1117, 557, 0, 0, 90, 1);
    pDerivedObj->info_btn->img[0] = al_load_bitmap("assets/image/info_btn_0.png");
    pDerivedObj->info_btn->img[1] = al_load_bitmap("assets/image/info_btn_1.png");

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
void menu_update(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));

    Button_Update(Obj->new_btn);
    Button_Update(Obj->save_btn);
    Button_Update(Obj->info_btn);

    if (Obj->new_btn->isPress)
    {
        self->scene_end = true;
        window = 1;
    }
    
    return;
}
void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->new_btn);
    Draw_Button(Obj->save_btn);
    Draw_Button(Obj->info_btn);
}
void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));

    // Destroy bitmap resources
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }
    
    // Destroy button images
    for(int i = 0; i < 2; i++) {
        if (Obj->info_btn->img[i]) {
            al_destroy_bitmap(Obj->info_btn->img[i]);
            Obj->info_btn->img[i] = NULL;
        }
        if (Obj->save_btn->img[i]) {
            al_destroy_bitmap(Obj->save_btn->img[i]);
            Obj->save_btn->img[i] = NULL;
        }
        if (Obj->new_btn->img[i]) {
            al_destroy_bitmap(Obj->new_btn->img[i]);
            Obj->new_btn->img[i] = NULL;
        }
    }
    
    // Free button objects
    free(Obj->info_btn);
    Obj->info_btn = NULL;
    free(Obj->new_btn);
    Obj->new_btn = NULL;
    free(Obj->save_btn);
    Obj->save_btn = NULL;
    
    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}
