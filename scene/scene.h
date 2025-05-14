#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "../global.h"
#include "../element/element.h"
#include <stdbool.h>

typedef enum SceneType
{
    Menu_L = 0,
    Stage_L,
    Set_L,
    GameScene_L,
    New_Level1_0_L
} SceneType;

/*
   [scene object]
*/
typedef struct EPNode
{
    int id;
    Elements *ele;
    struct EPNode *next;
} EPNode;
typedef struct Element_vector
{
    Elements *arr[MAX_ELEMENT];
    int len;
} ElementVec;
typedef struct _Scene Scene;
typedef void (*fptrUpdate)(Scene *);
typedef void (*fptrDraw)(Scene *);
typedef void (*fptrDestroy)(Scene *);
struct _Scene
{
    int label;
    void *pDerivedObj;
    bool scene_end;
    int ele_num;
    EPNode *ele_list[MAX_ELEMENT];
    // interface for function
    fptrUpdate Update;
    fptrDraw Draw;
    fptrDestroy Destroy;
};
typedef struct _Button
{
    int x, y;
    int w, h;
    int r;
    bool isCircle;
    bool isHover;
    bool isPress;
    ALLEGRO_BITMAP *img[3];
}Button;
Scene *New_Scene(int label);
void _Register_elements(Scene *scene, Elements *ele);
void _Remove_elements(Scene *scene, Elements *ele);
ElementVec _Get_all_elements(Scene *scene);
ElementVec _Get_label_elements(Scene *scene, int label);
bool mouseInCircle(int x, int y, int r);
bool mouseInRect(int x, int y, int w, int h);
Button *New_Button(int x, int y, int w, int h, int r, bool isCircle);
void Draw_Button(Button *button);
bool mouseInButton(Button *button);
bool Button_Update(Button *button);
#endif
