#ifndef CHARATER_H_INCLUDED
#define CHARATER_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../scene/level1.h"
#include "../scene/camera.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>


/*
   [character object]
*/
typedef enum CharacterType
{
    STOP = 0,
    MOVE,
    JUMP,
    DEAD
} CharacterType;
typedef enum CharacterState
{
    level1 = 0,
    level2,
    level3

}CharacterState;
typedef struct _Character
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int total_state;                // know level
    int state;                      // the state of character
    ALLEGRO_BITMAP *img[5]; // gif for each state. 0: stop, 1: move, 2:dead, 3:bomb, 4:transport
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
    float velocity_y;      // 垂直速度
    float gravity;         // 重力加速度
    float jump_force;      // 跳躍力度
    bool is_jumping;       // 是否正在跳躍
    int chara_cnt;
    int change; 
    int move_step;
} Character;
Elements *New_Character(int label);
void _Character_update_position(Elements *self, int dx, int dy);
void Character_update(Elements *self);
void Character_interact(Elements *self, Elements *target);
void Character_draw(Elements *self);
void Character_destory(Elements *self);

#endif
