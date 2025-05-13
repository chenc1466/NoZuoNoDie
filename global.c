#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 1280;
const int HEIGHT = 720;
int window = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_SAMPLE *song;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;
int now_bgm = 0;
double now_vol = 0.5;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
int key_used[3] = {ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_SPACE};
Point mouse;
bool debug_mode = true;
