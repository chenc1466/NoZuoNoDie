#include "leaderboard.h"
#include "../global.h"
#include "../scene/sceneManager.h"
#include <stdio.h>
#include <string.h>

// 在 leaderboard.c 文件開頭添加全局變量定義
char selected_player_name[100] = "";
char selected_player_level[100] = "";
char selected_player_character[100] = "";
int selected_line = 0;
bool save_clicked = false;  // 添加點擊狀態控制
int count = 0;
char line[256];
Scene *New_Leaderboard(int label)
{
    Leaderboard *pDerivedObj = (Leaderboard *)malloc(sizeof(Leaderboard));
    Scene *pObj = New_Scene(label);
    
    // 加載資源
    pDerivedObj->font = al_load_ttf_font("assets/font/shlop.otf", 48, 0);
    pDerivedObj->title_font = al_load_ttf_font("assets/font/shlop.otf", 48, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/menu.jpg");
    
    // 創建返回按鈕
    pDerivedObj->back_btn = New_Button(72, 550, 0, 0, 90, 1);
    pDerivedObj->back_btn->img[0] = al_load_bitmap("assets/image/back_btn_0.png");
    pDerivedObj->back_btn->img[1] = al_load_bitmap("assets/image/back_btn_1.png");
    
    // 創建保存按鈕
    pDerivedObj->save_btn = New_Button(1112, 550, 0, 0, 90, 1);
    pDerivedObj->save_btn->img[0] = al_load_bitmap("assets/image/savefile_btn_0.png");
    pDerivedObj->save_btn->img[1] = al_load_bitmap("assets/image/savefile_btn_1.png");
    
    // 初始化記錄
    pDerivedObj->record_count = 0;
    memset(pDerivedObj->names, 0, sizeof(pDerivedObj->names));
    
    // 讀取排行榜數據
    FILE *fptr = fopen("account.txt", "r");
    if (fptr != NULL) {
        
        
        while (fgets(line, sizeof(line), fptr) && count < 100) {
            char *token = strtok(line, ",");
            int col = 0;
            while (token != NULL && col < 3) {
                // 移除換行符和空格
                token[strcspn(token, "\n")] = 0;
                while (*token == ' ') token++;  // 跳過前導空格
                
                strcpy(pDerivedObj->names[count][col], token);
                token = strtok(NULL, ",");
                col++;
            }
            count++;
        }
        pDerivedObj->record_count = count;
        printf("record_count: %d\n", pDerivedObj->record_count);
        fclose(fptr);
    }
    
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = leaderboard_update;
    pObj->Draw = leaderboard_draw;
    pObj->Destroy = leaderboard_destroy;
    
    return pObj;
}

void leaderboard_update(Scene *self)
{
    Leaderboard *Obj = ((Leaderboard *)(self->pDerivedObj));
    
    // 獲取滑鼠狀態
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);
    int mouse_x = mouse_state.x;
    int mouse_y = mouse_state.y;
    
    // 檢查返回按鈕
    if(mouse_x >= 72 && mouse_x <= 162 && mouse_y >= 550 && mouse_y <= 640){
        Obj->back_btn->isHover = true;
        
        // 檢查點擊
        if(mouse_state.buttons & 1) {
            read_save = 1;
            finish_level = atoi(selected_player_level);
            current_character = atoi(selected_player_character);
            self->scene_end = true;
            window = 0;  // 返回主菜單
        }
    } else {
        Obj->back_btn->isHover = false;
    }
    Button_Update(Obj->save_btn);
    if(Obj->save_btn->isPress){
        save_clicked = true;
    }
    if(Obj->save_btn->isHover){
        Obj->save_btn->isHover = true;
    } else {
        Obj->save_btn->isHover = false;
    }
    
    // 檢查點擊排行榜內容
    if(mouse_state.buttons & 1) {  // 左鍵點擊
        // 檢查是否點擊 SAVE 文字
        if(mouse_y >= 550 - 20 && mouse_y <= 550 + 25 &&
           mouse_x >= WIDTH - 162 - 50 && mouse_x <= WIDTH - 72 + 50) {
            // 確保只觸發一次
            if (!save_clicked) {
                save_clicked = true;
                // 直接追加到 account.txt
                fclose(fptr);
                FILE *file = fopen("account.txt", "a+");
                if (file != NULL) {
                    // 寫入選中的內容
                    fprintf(file, "%s %s %s\n", 
                           selected_player_name, 
                           selected_player_level, 
                           selected_player_character);
                    fclose(file);
                    printf("Successfully appended to account.txt\n");
                    
                    FILE *fptr = fopen("account.txt", "r");
                    while (fgets(line, sizeof(line), fptr) && count < 100) {
                        char *token = strtok(line, ",");
                        int col = 0;
                        while (token != NULL && col < 3) {
                            // 移除換行符和空格
                            token[strcspn(token, "\n")] = 0;
                            while (*token == ' ') token++;  // 跳過前導空格
                            
                            strcpy(Obj->names[count][col], token);
                            token = strtok(NULL, ",");
                            col++;
                        }
                        count++;
                    }
                    Obj->record_count = count;
                    printf("record_count: %d\n", Obj->record_count);
                } else {
                    printf("Error opening account.txt\n");
                }
            }
            return;
        }
        
        int cnt = 0;
        for(int i = Obj->record_count - 1; i > Obj->record_count - 6; i--) {
            // 檢查是否點擊在該行，同時限制X軸範圍
            if(mouse_y >= 420 + cnt * 50 - 20 && mouse_y <= 420 + cnt * 50 + 25 &&
               mouse_x >= WIDTH/2 - 350 && mouse_x <= WIDTH/2 + 350) {  // 限制X軸範圍
                // 獲取該行的內容
                char selected_name[100];
                char selected_level[100];
                char selected_character[100];
                strcpy(selected_name, Obj->names[i][0]);
                strcpy(selected_level, Obj->names[i][1]);
                strcpy(selected_character, Obj->names[i][2]); 
                
                // 在這裡處理選中的內容
                printf("Selected player: %s, Level: %s, Character: %s\n", 
                       selected_name, selected_level, selected_character);
                
                // 可以將選中的內容存儲到全局變量中
                strcpy(selected_player_name, selected_name);
                strcpy(selected_player_level, selected_level);
                strcpy(selected_player_character, selected_character);
                
                break;
            }
            cnt++;
        }
    } else {
        // 當滑鼠按鈕釋放時，重置點擊狀態
        save_clicked = false;
    }
}

void leaderboard_draw(Scene *self)
{
    Leaderboard *Obj = ((Leaderboard *)(self->pDerivedObj));
    
    // 獲取滑鼠狀態
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);
    int mouse_y = mouse_state.y;
    int mouse_x = mouse_state.x;
    
    // 繪製背景
    al_draw_bitmap(Obj->background, 0, 0, 0);
    
    // 定義顏色
    ALLEGRO_COLOR normal_color = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR hover_color = al_map_rgb(244, 158, 76);  // 橙色
    
    // 繪製表頭
    al_draw_text(Obj->font, normal_color, WIDTH / 2 - 300, 350, ALLEGRO_ALIGN_CENTER, "Rank");
    al_draw_text(Obj->font, normal_color, WIDTH / 2, 350, ALLEGRO_ALIGN_CENTER, "Name");
    al_draw_text(Obj->font, normal_color, WIDTH / 2 + 300, 350, ALLEGRO_ALIGN_CENTER, "Level");

    int cnt = 0;
    // 繪製記錄
    for(int i = Obj->record_count - 1; i > Obj->record_count - 6; i--) {
        char rank[10];
        sprintf(rank, "%d", cnt + 1);
        
        // 檢查滑鼠是否在該行上，同時限制X軸範圍
        bool row_hover = (mouse_y >= 420 + cnt * 50 - 20 && mouse_y <= 420 + cnt * 50 + 25 &&
                         mouse_x >= WIDTH/2 - 350 && mouse_x <= WIDTH/2 + 350);
        
        // 使用相同的顏色繪製該行的所有文字
        ALLEGRO_COLOR current_color = row_hover ? hover_color : normal_color;
        
        // 繪製排名
        al_draw_text(Obj->font, current_color, 
                    WIDTH / 2 - 310, 420 + cnt * 50, 0, rank);
        
        // 繪製名字
        al_draw_text(Obj->font, current_color, 
                    WIDTH / 2 - 40, 420 + cnt * 50, 0, Obj->names[i][0]);
        
        // 繪製等級
        al_draw_text(Obj->font, current_color, 
                    WIDTH / 2 + 290, 420 + cnt * 50, 0, Obj->names[i][1]);
        
        cnt++;
    }    
    // 繪製返回按鈕
    Draw_Button(Obj->back_btn);
    Draw_Button(Obj->save_btn);
}

void leaderboard_destroy(Scene *self)
{
    Leaderboard *Obj = ((Leaderboard *)(self->pDerivedObj));
    
    // 釋放資源
    al_destroy_font(Obj->font);
    al_destroy_font(Obj->title_font);
    al_destroy_bitmap(Obj->background);
    
    // 釋放按鈕資源
    if (Obj->back_btn) {
        for (int i = 0; i < 2; i++) {
            if (Obj->back_btn->img[i]) {
                al_destroy_bitmap(Obj->back_btn->img[i]);
            }
        }
        free(Obj->back_btn);
    }
    
    if (Obj->save_btn) {
        for (int i = 0; i < 2; i++) {
            if (Obj->save_btn->img[i]) {
                al_destroy_bitmap(Obj->save_btn->img[i]);
            }
        }
        free(Obj->save_btn);
    }
    
    // 釋放場景對象
    free(Obj);
    self->pDerivedObj = NULL;
    free(self);
} 