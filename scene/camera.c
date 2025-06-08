#include "camera.h"

void init_camera(Camera* camera, float width, float height) {
    camera->x = 0;
    camera->y = 0;
    camera->width = width;
    camera->height = height;
}

void update_camera(Camera* camera, float player_x, float player_y, float map_width, float map_height) {
    // Calculate target camera position (center on player)
    float target_x = player_x - (camera->width / 2);
    float target_y = player_y - (camera->height / 2);

    // Clamp camera position to map bounds
    if (target_x < 0) target_x = 0;
    if (target_y < 0) target_y = 0;
    if (target_x > map_width - camera->width) target_x = map_width - camera->width;
    if (target_y > map_height - camera->height) target_y = map_height - camera->height;

    // Update camera position
    camera->x = target_x;
    camera->y = target_y;
}

void update_camera_with_deadzone(Camera *camera, Player *player, int map_width, int map_height, int deadzone_width, int deadzone_height) {
    float deadzone_left = camera->x + (camera->width  - deadzone_width) / 2;
    float deadzone_right = camera->x + (camera->width + deadzone_width) / 2;
    float deadzone_top = camera->y + (camera->height - deadzone_height) / 2;
    float deadzone_bottom = camera->y + (camera->height + deadzone_height) / 2;

    if (player->x < deadzone_left) {
        camera->x -= (deadzone_left - player->x);
    } else if (player->x + player->width > deadzone_right) {
        camera->x += (player->x + player->width - deadzone_right);
    }

    if (player->y < deadzone_top) {
        camera->y -= (deadzone_top - player->y);
    } else if (player->y + player->height > deadzone_bottom) {
        camera->y += (player->y + player->height - deadzone_bottom);
    }

    // Clamp camera to map bounds
    if (camera->x < 0) camera->x = 0;
    if (camera->y < 0) camera->y = 0;
    if (camera->x > map_width - camera->width) camera->x = map_width - camera->width;
    if (camera->y > map_height - camera->height) camera->y = map_height - camera->height;
}