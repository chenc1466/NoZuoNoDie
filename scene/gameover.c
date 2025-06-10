#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include "gameover.h"
#include <stdbool.h>
#include "../global.h"
/*
   [Stage Select function]
*/
Scene *New_Gameover(int label)
{
    Gameover *pDerivedObj = (Gameover *)malloc(sizeof(Gameover));
    Scene *pObj = New_Scene(label);
    // Background
    //printf("ff %d\n", dead_type);
    if(dead_type == 1){
        pDerivedObj->background = al_load_bitmap("assets/image/gameover1.png");
    }
    else if(dead_type == 2){
        pDerivedObj->background = al_load_bitmap("assets/image/gameover2.png");
    }
    else if(dead_type == 3){
        pDerivedObj->background = al_load_bitmap("assets/image/gameover3.png");
    }
    else if(dead_type == 4){
        pDerivedObj->background = al_load_bitmap("assets/image/gameover4.jpg");
    }

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

        // gameover Sound
    pDerivedObj->gameover_sound = al_load_sample("assets/sound/roar.wav");
    if(sample_instance){
        al_stop_sample_instance(sample_instance);
    }
    if(pDerivedObj->gameover_sound){
        pDerivedObj->gameover_instance = al_create_sample_instance(pDerivedObj->gameover_sound);
        al_attach_sample_instance_to_mixer(pDerivedObj->gameover_instance, al_get_default_mixer());
        al_play_sample_instance(pDerivedObj->gameover_instance);
        pDerivedObj->gameover_instance = pDerivedObj->gameover_instance;
        pDerivedObj->gameover_sound_played = true;
    }


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
        if(level_state == 1){
            self->scene_end = true;
            window = 3;
        }
        else if(level_state == 2){
            self->scene_end = true;
            window = 6;
        }
        else if(level_state == 3){
            self->scene_end = true;
            window = 7;
        }
    }
    return;
    if(Obj->gameover_sound_played && Obj->gameover_instance){
        if(!al_get_sample_instance_playing(Obj->gameover_instance)){
            al_destroy_sample_instance(sample_instance);
            Obj->gameover_instance = NULL;
            al_destroy_sample_instance(Obj->gameover_instance);
            Obj->gameover_sound_played = false;
        }
    }
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

