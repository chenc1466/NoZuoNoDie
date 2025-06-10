#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include "victory.h"
#include "../global.h"
#include <stdbool.h>
/*
   [Stage Select function]
*/
Scene *New_Victory(int label)
{
    Victory *pDerivedObj = (Victory *)malloc(sizeof(Victory));
    Scene *pObj = New_Scene(label);

    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/victory.png");

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

    // Victory Sound
    pDerivedObj->victory_sound = al_load_sample("assets/sound/cheer.wav");
    if(sample_instance){
        al_stop_sample_instance(sample_instance);
    }
    if(pDerivedObj->victory_sound){
        pDerivedObj->victory_instance = al_create_sample_instance(pDerivedObj->victory_sound);
        al_attach_sample_instance_to_mixer(pDerivedObj->victory_instance, al_get_default_mixer());
        al_play_sample_instance(pDerivedObj->victory_instance);
        pDerivedObj->victory_instance = pDerivedObj->victory_instance;
        pDerivedObj->victory_sound_played = true;
    }

    pObj->Update = victory_update;
    pObj->Draw = victory_draw;
    pObj->Destroy = victory_destroy;
    return pObj;
}
void victory_update(Scene *self)
{
    Victory*Obj = ((Victory *)(self->pDerivedObj));
    Button_Update(Obj->restart_btn);
    Button_Update(Obj->back_btn);  
    if (Obj->back_btn->isPress)
    {
        self->scene_end = true;
        window = 1;
    }
    if (Obj->restart_btn->isPress)
    {
        printf("level_state: %d\n", level_state);
        if(level_state == 1){
            self->scene_end = true;
            window = 2;
        }
        else if(level_state == 2){
            self->scene_end = true;
            window = 6;
        }
    }
        if(Obj->victory_sound_played && Obj->victory_instance){
        if(!al_get_sample_instance_playing(Obj->victory_instance)){
            al_destroy_sample_instance(sample_instance);
            Obj->victory_instance = NULL;
            al_destroy_sample_instance(Obj->victory_instance);
            Obj->victory_sound_played = false;
        }
    }
    return;
}
void victory_draw(Scene *self)
{
    Victory *Obj = ((Victory *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->back_btn);
    Draw_Button(Obj->restart_btn);
}
void victory_destroy(Scene *self)
{
    Victory *Obj = ((Victory *)(self->pDerivedObj));
    
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

