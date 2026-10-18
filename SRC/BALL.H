#ifndef BALL_H
#define BALL_H

#include "gameobj.h"

#define BALL_SPEED 2.0
#define BALL_WIDTH 3
#define BALL_HEIGHT 3
#define BALL_RESET_OFFSET_Y 3

typedef struct ball {
    game_object base;
    velocity velocity;

    void (*new)(struct ball*, float, float, char);
    void (*move)(struct ball*);
    void (*draw)(const struct ball*);
    void (*reset)(struct ball*, float, float);
} ball;

void init_ball(ball* this);
  
#endif