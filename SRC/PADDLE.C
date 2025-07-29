#include "PADDLE.H"
#include "CONF.H"
#include "RENDERER.H"

#define PADDLE_SPEED 2.0
#define PADDLE_WIDTH 30
#define PADDLE_HEIGHT 5

static void paddleNew(Paddle* this, float x, float y, char color);
static void paddleMove(Paddle* this, Direction direction);
static void paddleDraw(const Paddle* this);

void paddleInit(Paddle* this) {
    this->new = paddleNew;
    this->move = paddleMove;
    this->draw = paddleDraw;
}

static void paddleNew(Paddle* this, float x, float y, char color) {
    GAMEOBJ(this)->position.x = x;
    GAMEOBJ(this)->position.y = y;
    GAMEOBJ(this)->width = PADDLE_WIDTH;
    GAMEOBJ(this)->height = PADDLE_HEIGHT;
    GAMEOBJ(this)->color = color;
    this->velocity.x = PADDLE_SPEED;
    this->velocity.y = 0.0;
}

static void paddleMove(Paddle* this, Direction direction) {
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

static void paddleDraw(const Paddle* this) {
    rndDrawRect(
        GAMEOBJ(this)->position.x, 
        GAMEOBJ(this)->position.y, 
        GAMEOBJ(this)->width, 
        GAMEOBJ(this)->height, 
        GAMEOBJ(this)->color);
}