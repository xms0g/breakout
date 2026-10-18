#include "aabb.h"
#include "gameobj.h"

int check_aabb(const struct game_object* one, const struct game_object* two) {
    // collision x-axis?
    int collision_x = one->position.x + one->width >= two->position.x &&
        two->position.x + two->width >= one->position.x;
    // collision y-axis?
    int collision_y = one->position.y + one->height >= two->position.y &&
        two->position.y + two->height >= one->position.y;
    // collision only if on both axes
    return collision_x && collision_y;
}
