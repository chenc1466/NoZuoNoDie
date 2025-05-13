#include <allegro5/allegro_primitives.h>
#include "set.h"
#include <stdbool.h>

/*
   [Set function]
*/
Scene *New_Set(int label)
{
    Set *pDerivedObj = (Set *)malloc(sizeof(Set));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/shlop.otf", 48, 0);
    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/set.jpg");
    
    // BGM1 Button
    pDerivedObj->bgm1_btn = New_Button(717, 218, 356, 92, 0, 0);
    pDerivedObj->bgm1_btn->img[0] = al_load_bitmap("assets/image/bgm1_btn_0.png");
    pDerivedObj->bgm1_btn->img[1] = al_load_bitmap("assets/image/bgm1_btn_1.png");
    pDerivedObj->bgm1_btn->img[2] = al_load_bitmap("assets/image/bgm1_btn_2.png");
    // BGM2 Button
    pDerivedObj->bgm2_btn = New_Button(708, 323, 375, 92, 0, 0);
    pDerivedObj->bgm2_btn->img[0] = al_load_bitmap("assets/image/bgm2_btn_0.png");
    pDerivedObj->bgm2_btn->img[1] = al_load_bitmap("assets/image/bgm2_btn_1.png");
    pDerivedObj->bgm2_btn->img[2] = al_load_bitmap("assets/image/bgm2_btn_2.png");

    // Vol1 Button
    pDerivedObj->vol1_btn = New_Button(884, 449, 0, 0, 50, 1);
    pDerivedObj->vol1_btn->img[0] = al_load_bitmap("assets/image/vol1_btn_0.png");
    pDerivedObj->vol1_btn->img[1] = al_load_bitmap("assets/image/vol1_btn_1.png");
    
    // Vol2 Button
    pDerivedObj->vol2_btn = New_Button(1012, 449, 0, 0, 50, 1);
    pDerivedObj->vol2_btn->img[0] = al_load_bitmap("assets/image/vol2_btn_0.png");
    pDerivedObj->vol2_btn->img[1] = al_load_bitmap("assets/image/vol2_btn_1.png");

    // Back Button
    pDerivedObj->back_btn = New_Button(27, 40, 0, 0, 90, 1);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = set_update;
    pObj->Draw = set_draw;
    pObj->Destroy = set_destroy;
    return pObj;
}
int wait = 0;
void set_update(Scene *self)
{
    Set *Obj = ((Set *)(self->pDerivedObj));
    Button_Update(Obj->back_btn);
        
    if (Obj->back_btn->isPress)
    {
        self->scene_end = true;
        window = 1;
    }
    Button_Update(Obj->bgm1_btn);
    Button_Update(Obj->bgm2_btn);
    Button_Update(Obj->vol1_btn);
    Button_Update(Obj->vol2_btn);
    if(Obj->bgm1_btn->isPress){
        switch_bgm(0);
        now_bgm = 0;
    }
    if(Obj->bgm2_btn->isPress){
        switch_bgm(1);
        now_bgm = 1;
    }  
    if(Obj->vol1_btn->isPress && !wait){
        if(now_vol > 0) now_vol -= 0.1;
        wait = 1;
        al_set_sample_instance_gain(sample_instance, now_vol);
    }
    if(Obj->vol2_btn->isPress && !wait){
        if(now_vol < 1) now_vol += 0.1;
        wait = 1;
        al_set_sample_instance_gain(sample_instance, now_vol);
    }
    if(wait && !Obj->vol1_btn->isPress && !Obj->vol2_btn->isPress){
        wait = 0;
    }

    return;
}
void set_draw(Scene *self)
{
    
    Set *Obj = ((Set *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->back_btn);
    al_draw_bitmap(Obj->bgm1_btn->img[now_bgm == 0 ? 2 : Obj->bgm1_btn->isHover], Obj->bgm1_btn->x, Obj->bgm1_btn->y, 0);
    al_draw_bitmap(Obj->bgm2_btn->img[now_bgm == 1 ? 2 : Obj->bgm2_btn->isHover], Obj->bgm2_btn->x, Obj->bgm2_btn->y, 0);
    al_draw_bitmap(Obj->vol1_btn->img[Obj->vol1_btn->isHover], Obj->vol1_btn->x, Obj->vol1_btn->y, 0);
    al_draw_bitmap(Obj->vol2_btn->img[Obj->vol2_btn->isHover], Obj->vol2_btn->x, Obj->vol2_btn->y, 0);
    char vol[4];
    sprintf(vol, "%d", (int)(now_vol * 10));
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), 975, 445, 1, vol );
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), 451, 234, 1, al_keycode_to_name(key_used[0]) );
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), 451, 339, 1, al_keycode_to_name(key_used[1]) );
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), 451, 445, 1, al_keycode_to_name(key_used[2]) );
}
void set_destroy(Scene *self)
{
    Set *Obj = ((Set *)(self->pDerivedObj));
    
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
    
    // Destroy button images
    for(int i = 0; i < 2; i++) {
        if (Obj->back_btn->img[i]) {
            al_destroy_bitmap(Obj->back_btn->img[i]);
            Obj->back_btn->img[i] = NULL;
        }
    }
    
    // Free button object
    free(Obj->back_btn);
    Obj->back_btn = NULL;
    
    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}
