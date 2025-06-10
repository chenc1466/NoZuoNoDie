#include <allegro5/allegro_primitives.h>
#include "name_input.h"
#include <stdbool.h>
/*
   [Menu function]
*/
char player_name[100][100] = {"name"};
int name[1];
Scene *New_NameInput(int label)
{
    NameInput *pDerivedObj = (NameInput *)malloc(sizeof(NameInput));
    Scene *pObj = New_Scene(label);
    pDerivedObj->font = al_load_ttf_font("assets/font/shlop.otf", 48, 0);
    pDerivedObj->title_font = al_load_ttf_font("assets/font/shlop.otf", 36, 0);
    pDerivedObj->name_length = 0;
    pDerivedObj->is_active = true;
    memset(pDerivedObj->name, 0, sizeof(pDerivedObj->name));
    // Background
    pDerivedObj->background = al_load_bitmap("assets/image/menu.jpg");

    // Ctr Button
    pDerivedObj->ctr_btn[0] = New_Button(WIDTH / 2 - 100, 450, 300, 50,  0, 0);
    pDerivedObj->ctr_btn[0]->img[0] = al_load_bitmap("assets/image/ctr_btn_0.png");
    pDerivedObj->ctr_btn[0]->img[1] = al_load_bitmap("assets/image/ctr_btn_1.png");
    pDerivedObj->button_now = 0;
    fptr = fopen("account.txt", "r"); // Opens "filename.txt" in read mode
    if (fptr == NULL) {
        printf("Error opening file.\n");
    }
    fclose(fptr);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = name_input_update;
    pObj->Draw = name_input_draw;
    pObj->Destroy = name_input_destroy;
    return pObj;
}
void name_input_update(Scene *self)
{
    NameInput *Obj = ((NameInput *)(self->pDerivedObj));
    ALLEGRO_KEYBOARD_STATE keyboard_state;
    static int input_delay = 0;  // 添加延遲計數器
    al_get_keyboard_state(&keyboard_state);

    if(Obj->ctr_btn[0]->isPress){
        name_state = 1;
        now_ctr = -1;
        Obj->button_now = 1;
    }

    if(Obj->button_now == 1){
        // 增加延遲計數
        if(input_delay > 0) {
            input_delay--;
        }

        // 只有在延遲結束後才處理輸入
        if(input_delay == 0) {
            bool key_pressed = false;  // 用於檢測是否有按鍵被按下

            // 檢測字母和數字鍵
            for(int i = ALLEGRO_KEY_A; i <= ALLEGRO_KEY_Z; i++) {
                if(al_key_down(&keyboard_state, i)) {
                    if(Obj->name_length < 19) {
                        char c = 'A' + (i - ALLEGRO_KEY_A);
                        if(!(al_key_down(&keyboard_state, ALLEGRO_KEY_LSHIFT) || 
                             al_key_down(&keyboard_state, ALLEGRO_KEY_RSHIFT))) {
                            c = 'a' + (i - ALLEGRO_KEY_A);
                        }
                        Obj->name[Obj->name_length++] = c;
                        Obj->name[Obj->name_length] = '\0';
                        strcpy(player_name[0], Obj->name);
                        strcpy(account[0], player_name[0]);  // 同步更新 account[0]
                        key_pressed = true;
                    }
                }
            }

            // 檢測數字鍵
            for(int i = ALLEGRO_KEY_0; i <= ALLEGRO_KEY_9; i++) {
                if(al_key_down(&keyboard_state, i)) {
                    if(Obj->name_length < 19) {
                        Obj->name[Obj->name_length++] = '0' + (i - ALLEGRO_KEY_0);
                        Obj->name[Obj->name_length] = '\0';
                        strcpy(player_name[0], Obj->name);
                        strcpy(account[0], player_name[0]);  // 同步更新 account[0]
                        key_pressed = true;
                    }
                }
            }

            // 檢測退格鍵
            if(al_key_down(&keyboard_state, ALLEGRO_KEY_BACKSPACE)) {
                if(Obj->name_length > 0) {
                    Obj->name[--Obj->name_length] = '\0';
                    strcpy(player_name[0], Obj->name);
                    strcpy(account[0], player_name[0]);  // 同步更新 account[0]
                    key_pressed = true;
                }
            }

            // 檢測空格鍵
            if(al_key_down(&keyboard_state, ALLEGRO_KEY_SPACE)) {
                if(Obj->name_length < 19) {
                    Obj->name[Obj->name_length++] = ' ';
                    Obj->name[Obj->name_length] = '\0';
                    strcpy(player_name[0], Obj->name);
                    strcpy(account[0], player_name[0]);  // 同步更新 account[0]
                    key_pressed = true;
                }
            }

            // 檢測回車鍵
            if(al_key_down(&keyboard_state, ALLEGRO_KEY_ENTER)) {
                if(Obj->name_length > 0) {
                    strcpy(player_name[0], Obj->name);
                    strcpy(account[0], player_name[0]);  // 同步更新 account[0]
                    Obj->is_active = false;
                    self->scene_end = true;
                    window = 8;
                    key_pressed = true;

                    // 保存玩家信息到文件
                    FILE *fptr = fopen("account.txt", "a+");
                    if (fptr != NULL) {
                        fprintf(fptr, "%s, 0, 0\n", account[0]);  // 記錄名字和初始等級
                        fclose(fptr);
                        printf("Player account saved: %s\n", account[0]);
                    } else {
                        printf("Error: Could not open account.txt for writing\n");
                    }
                }
            }

            // 如果有按鍵被按下，設置延遲
            if(key_pressed) {
                input_delay = 10;  // 設置延遲時間（可以根據需要調整）
            }
        }
    }

    Button_Update(Obj->ctr_btn[0]);
    return;
}
void name_input_draw(Scene *self)
{
    NameInput *Obj = ((NameInput *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    Draw_Button(Obj->ctr_btn[0]);

    
    // 繪製當前輸入的名字
    al_draw_bitmap(Obj->ctr_btn[0]->img[now_ctr == 0 ? 2 : Obj->ctr_btn[0]->isHover], Obj->ctr_btn[0]->x, Obj->ctr_btn[0]->y, 0);
    
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR gray = al_map_rgb(175, 175, 175);
    ALLEGRO_COLOR orange = al_map_rgb(244, 158, 76);
    al_draw_text(Obj->font, (now_ctr == 0 ? orange :(Obj->ctr_btn[0]->isHover ? gray : white)), WIDTH / 2, 455, 1, player_name[0]);
    
   
    // 繪製提示文字
    al_draw_text(Obj->font, al_map_rgb(200, 200, 200),
                 WIDTH / 2, 600,
                 ALLEGRO_ALIGN_CENTER, "Press Enter to Start");
    
}

void name_input_destroy(Scene *self)
{
    NameInput *Obj = ((NameInput *)(self->pDerivedObj));

    // Destroy bitmap resources
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
        Obj->background = NULL;
    }
    al_destroy_font(Obj->font);
    al_destroy_font(Obj->title_font);


    
    
    // Free the scene objects
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
}
