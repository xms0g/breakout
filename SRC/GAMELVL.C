#include "GAMELVL.H"
#include <string.h>
#include "RENDERER.H"

#define BRICK_WIDTH     20
#define BRICK_HEIGHT    5
#define ADJ             3
#define START_ADJ       12

static const int brickHitCountTable[16] = {0,0,1,0,3,0,4,0,0,0,0,0,2,0,1,0};

static void glNew(GameLevel* this, const int (*level)[COL]);
static void glUpdate(GameLevel* this);
static void glDraw(const GameLevel* this);
static int glIsFinished(const GameLevel* this);
static Brick* glGetBrick(GameLevel* this, int index);

void glInit(GameLevel* this) {
    this->new = glNew;
    this->isFinished = glIsFinished;
    this->update = glUpdate;
    this->draw = glDraw;
    this->getBrick = glGetBrick;

    this->activeBrickCount = 0;
    
    memset(this->bricks, 0, sizeof(this->bricks));
}

static void glNew(GameLevel* this, const int (*level)[COL]) {
    int startX = 0;
    int startY = 30;
    int posx, posy;
    int i, j;
    Brick obj;
    
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < COL; ++j) {
            int color = level[i][j];
            
            if (color == 0x0) {
                continue;
            }
            
            posx = startX + START_ADJ;
            posy = startY;

            GAMEOBJ(&obj)->position.x = posx;
            GAMEOBJ(&obj)->position.y = posy;
            GAMEOBJ(&obj)->width = BRICK_WIDTH;
            GAMEOBJ(&obj)->height = BRICK_HEIGHT;
            GAMEOBJ(&obj)->color = color;
            obj.isActive = 1;
            obj.hitCount = brickHitCountTable[color];
           
            this->bricks[this->activeBrickCount++] = obj;
            startX += (BRICK_WIDTH + ADJ);
        }
      
        startX = 0;
        startY += (BRICK_HEIGHT + ADJ);
    }
}

static void glUpdate(GameLevel* this) {
    if (this->activeBrickCount == 0) {
        return;
    }

    this->activeBrickCount--;
}

static void glDraw(const GameLevel* this) {
    int i;
    for (i = 0; i < BRICK_COUNT; ++i) {
        Brick* brick = &this->bricks[i];

        if (!brick->isActive) {
            continue;
        }
      
        rndDrawRect(
            GAMEOBJ(brick)->position.x, 
            GAMEOBJ(brick)->position.y, 
            GAMEOBJ(brick)->width, 
            GAMEOBJ(brick)->height, 
            GAMEOBJ(brick)->color);
    }
}

static int glIsFinished(const GameLevel* this) {
    return this->activeBrickCount == 0;
}

static Brick* glGetBrick(GameLevel* this, int index) {
    if (index < 0 || index >= BRICK_COUNT) {
        return NULL;
    }
    
    return &this->bricks[index];
}