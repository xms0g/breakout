#include "paddle.h"
#include "conf.h"
#include "renderer.h"

#define PADDLE_SPEED 2.0
#define PADDLE_WIDTH 30
#define PADDLE_HEIGHT 5

static void new(paddle* this, float x, float y, char color);
static void move(paddle* this, direction direction);
static void draw(const paddle* this);

void init_paddle(paddle* this) {
    this->new = new;
    this->move = move;
    this->draw = draw;
}

static void new(paddle* this, float x, float y, char color) {
    GAMEOBJ(this)->position.x = x;
    GAMEOBJ(this)->position.y = y;
    GAMEOBJ(this)->width = PADDLE_WIDTH;
    GAMEOBJ(this)->height = PADDLE_HEIGHT;
    GAMEOBJ(this)->color = color;
    this->velocity.x = PADDLE_SPEED;
    this->velocity.y = 0.0;
}

static void move(paddle* this, direction direction) {
    switch (direction) {
        case LEFT:
            if (GAMEOBJ(this)->position.x > 0) {
                GAMEOBJ(this)->position.x -= this->velocity.x;
            }
            break;
        case RIGHT:
            if (GAMEOBJ(this)->position.x < SCREEN_WIDTH - GAMEOBJ(this)->width) {
                GAMEOBJ(this)->position.x += this->velocity.x;
            }
            break;
        default:
            break;
    }
}

static void draw(const paddle* this) {
    rnd_draw_rect(
        GAMEOBJ(this)->position.x, 
        GAMEOBJ(this)->position.y, 
        GAMEOBJ(this)->width, 
        GAMEOBJ(this)->height, 
        GAMEOBJ(this)->color);
}