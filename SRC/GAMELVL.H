#ifndef GAMELVL_H
#define GAMELVL_H

#include "gameobj.h"
#include "conf.h"

typedef struct brick {
    game_object base;
    int isActive;
    int hitCount;
} brick;

typedef struct game_level {
    brick bricks[BRICK_COUNT];
    int active_brick_count;

    void (*new)(struct game_level*, const int (*level)[COL]);
    void (*update)(struct game_level*);
    void (*draw)(const struct game_level*);
    int (*is_finished)(const struct game_level*);
    brick* (*get_brick)(struct game_level*, int);
} game_level;

void init_game_lvl(game_level* this);

#endif