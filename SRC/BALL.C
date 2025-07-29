#include "BALL.H"
#include "CONF.H"
#include "RENDERER.H"

static void ballNew(Ball* this, float x, float y, char color);
static void ballMove(Ball* this);
static void ballDraw(const Ball* this);
static void ballReset(Ball* this, float x, float y);

void ballInit(Ball* this) {
    this->new = ballNew;
    this->move = ballMove;
    this->draw = ballDraw;
    this->reset = ballReset;   
}

static void ballNew(Ball* this, float x, float y, char color) {
    GAMEOBJ(this)->position.x = x;
    GAMEOBJ(this)->position.y = y;
    GAMEOBJ(this)->width = BALL_WIDTH;
    GAMEOBJ(this)->height = BALL_HEIGHT;
    GAMEOBJ(this)->color = color;
    this->velocity.x = -BALL_SPEED/2;
    this->velocity.y = -BALL_SPEED/2;
}

static void ballMove(Ball* this) {
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

static void ballDraw(const Ball* this) {
    rndDrawRect(
        GAMEOBJ(this)->position.x, 
        GAMEOBJ(this)->position.y, 
        GAMEOBJ(this)->width, 
        GAMEOBJ(this)->height, 
        GAMEOBJ(this)->color);
}

static void ballReset(Ball* this, float x, float y) {
    GAMEOBJ(this)->position.x = x;
    GAMEOBJ(this)->position.y = y;
    this->velocity.x = -BALL_SPEED/2;
    this->velocity.y = -BALL_SPEED/2;
}
