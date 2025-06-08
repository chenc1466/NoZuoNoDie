// camera.h

#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Camera;

typedef struct {
    float x, y;
    int width, height;
} Player;

// Initialize camera with viewport size
void init_camera(Camera* camera, float width, float height);

// Update camera position to follow player
void update_camera(Camera* camera, float player_x, float player_y, float map_width, float map_height);

#endif
