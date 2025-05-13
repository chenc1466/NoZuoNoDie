#include "sceneManager.h"
#include "menu.h"
#include "stageselect.h"
#include "set.h"
#include "gamescene.h"
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
    default:
        break;
    }
}