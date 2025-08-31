#ifndef PADDLE_H
#define PADDLE_H

#include "gameobj.h"

typedef enum {
    LEFT,
    RIGHT
} Direction;

typedef struct Paddle {
    GameObject base;
    Velocity velocity;

    void (*new)(struct Paddle*, float, float, char);
    void (*move)(struct Paddle*, Direction);
    void (*draw)(const struct Paddle*);
} Paddle;

void paddleInit(Paddle* this);

#endif