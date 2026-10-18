#ifndef PADDLE_H
#define PADDLE_H

#include "gameobj.h"

typedef enum {
    LEFT,
    RIGHT
} direction;

typedef struct paddle {
    game_object base;
    velocity velocity;

    void (*new)(struct paddle*, float, float, char);
    void (*move)(struct paddle*, direction);
    void (*draw)(const struct paddle*);
} paddle;

void init_paddle(paddle* this);

#endif