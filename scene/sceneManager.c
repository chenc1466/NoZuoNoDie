#include "sceneManager.h"
#include "menu.h"
#include "stageselect.h"
#include "set.h"
#include "gamescene.h"
#include "level1.h"
#include "gameover.h"
#include "victory.h"

Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case Stage_L:
        scene = New_Stage(Stage_L);
        break;
    case Set_L:
        scene = New_Set(Set_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
    case Level1_L:
        scene = New_Level1(Level1_L);
        break;
    case Gameover_L:
        scene = New_Gameover(Gameover_L);
        break;
    case Victory_L:
        scene = New_Victory(Victory_L);
    default:
        break;
    }
}