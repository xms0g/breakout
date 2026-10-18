#include "ball.h"
#include "conf.h"
#include "renderer.h"

static void new_ball(ball* this, float x, float y, char color);
static void move_ball(ball* this);
static void draw_ball(const ball* this);
static void reset_ball(ball* this, float x, float y);

void init_ball(ball* this) {
    this->new = new_ball;
    this->move = move_ball;
    this->draw = draw_ball;
    this->reset = reset_ball;   
}

static void new_ball(ball* this, float x, float y, char color) {
    GAMEOBJ(this)->position.x = x;
    GAMEOBJ(this)->position.y = y;
    GAMEOBJ(this)->width = BALL_WIDTH;
    GAMEOBJ(this)->height = BALL_HEIGHT;
    GAMEOBJ(this)->color = color;
    this->velocity.x = -BALL_SPEED/2;
    this->velocity.y = -BALL_SPEED/2;
}

static void move_ball(ball* this) {
     GAMEOBJ(this)->position.x += this->velocity.x;
     GAMEOBJ(this)->position.y += this->velocity.y;

    if (GAMEOBJ(this)->position.x < 0) {
        GAMEOBJ(this)->position.x = 0;
        this->velocity.x = -this->velocity.x;
    } else if (GAMEOBJ(this)->position.x + GAMEOBJ(this)->width >= SCREEN_WIDTH) {
        GAMEOBJ(this)->position.x = SCREEN_WIDTH - GAMEOBJ(this)->width;
        this->velocity.x = -this->velocity.x;
    }

    if (GAMEOBJ(this)->position.y <= 0) {
        GAMEOBJ(this)->position.y = 0;
        this->velocity.y = -this->velocity.y;
    }
}

static void draw_ball(const ball* this) {
    rnd_draw_rect(
        GAMEOBJ(this)->position.x, 
        GAMEOBJ(this)->position.y, 
        GAMEOBJ(this)->width, 
        GAMEOBJ(this)->height, 
        GAMEOBJ(this)->color);
}

static void reset_ball(ball* this, float x, float y) {
    GAMEOBJ(this)->position.x = x;
    GAMEOBJ(this)->position.y = y;
    this->velocity.x = -BALL_SPEED/2;
    this->velocity.y = -BALL_SPEED/2;
}
