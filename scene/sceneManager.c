#include "sceneManager.h"
#include "menu.h"
#include "stageselect.h"
#include "set.h"
#include "gamescene.h"
#include "level1.h"
#include "gameover.h"
#include "victory.h"
#include "level2.h"
#include "level3.h"
#include "change.h"
#include "name_input.h"
#include "leaderboard.h"
#include "info1.h"
#include "info2.h"
#include "info3.h"
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
        break;
    case Level2_L:
        scene = New_Level2(Level2_L);
        break;
    case Level3_L:
        scene = New_Level3(Level3_L);
        break;
    case Change_L:
        scene = New_Change(Change_L);
        break;
    case NameInput_L:
        scene = New_NameInput(NameInput_L);
        break;
    case Leaderboard_L:
        scene = New_Leaderboard(Leaderboard_L);
        break;
    case Info1_L:
        scene = New_Info1(Info1_L);
        break;
    case Info2_L:
        scene = New_Info2(Info2_L);
        break;
    case Info3_L:
        scene = New_Info3(Info3_L);
        break;
    default:
        break;
    }
}