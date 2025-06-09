#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define GAME_TERMINATE -1
#include "shapes/Point.h"
#define debug(x)                                                            \
    if (x)                                                                  \
    {                                                                       \
        printf("check at line number %d in file %s\n", __LINE__, __FILE__); \
    }
#define MAX_ELEMENT 100
#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) < (y) ? (y) : (x))
// note that you can't assign initial value for extern variable!
extern const double FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern int window;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES];
extern Point mouse;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER *fps;
extern bool debug_mode;
extern ALLEGRO_SAMPLE *song;
extern ALLEGRO_SAMPLE_INSTANCE *sample_instance;
extern int key_used[3];
extern int now_bgm;
extern double now_vol;
extern int now_ctr;
extern int dead_cnt;
extern int bomb_cnt;
extern int dead_type;
extern int level_state;
extern int character_total_state;
extern int platform_state;
extern int level_state;
extern int camera_x;
extern int camera_y;
extern int finish_level;
extern int canyon1_y;
extern int canyon2_y;
extern int current_character;
extern FILE *fptr;
extern char account[2][100];
bool isColliding(int x1, int y1, int w1, int h1,
                 int x2, int y2, int w2, int h2);
#endif
