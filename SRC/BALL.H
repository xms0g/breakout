#ifndef BALL_H
#define BALL_H

#include "gameobj.h"

#define BALL_SPEED 2.0
#define BALL_WIDTH 3
#define BALL_HEIGHT 3
#define BALL_RESET_OFFSET_Y 3

typedef struct Ball {
    GameObject base;
    Velocity velocity;

    void (*new)(struct Ball*, float, float, char);
    void (*move)(struct Ball*);
    void (*draw)(const struct Ball*);
    void (*reset)(struct Ball*, float, float);
} Ball;

void ballInit(Ball* this);
  
#endif