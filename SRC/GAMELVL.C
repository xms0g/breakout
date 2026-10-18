#include "gamelvl.h"
#include <string.h>
#include "renderer.h"

#define BRICK_WIDTH     20
#define BRICK_HEIGHT    5
#define ADJ             3
#define START_ADJ       12

static const int brick_hit_count_table[16] = {0,0,1,0,3,0,4,0,0,0,0,0,2,0,1,0};

static void new(game_level* this, const int (*level)[COL]);
static void update(game_level* this);
static void draw(const game_level* this);
static int is_finished(const game_level* this);
static brick* get_brick(game_level* this, int index);

void init_game_lvl(game_level* this) {
    this->new = new;
    this->is_finished = is_finished;
    this->update = update;
    this->draw = draw;
    this->get_brick = get_brick;

    this->active_brick_count = 0;
    
    memset(this->bricks, 0, sizeof(this->bricks));
}

static void new(game_level* this, const int (*level)[COL]) {
    int start_x = 0;
    int start_y = 30;
    int pos_x, pos_y;
    int i, j;
    brick obj;
    
    for (i = 0; i < ROW; ++i) {
        for (j = 0; j < COL; ++j) {
            int color = level[i][j];
            
            if (color == 0x0) {
                continue;
            }
            
            pos_x = start_x + START_ADJ;
            pos_y = start_y;

            GAMEOBJ(&obj)->position.x = pos_x;
            GAMEOBJ(&obj)->position.y = pos_y;
            GAMEOBJ(&obj)->width = BRICK_WIDTH;
            GAMEOBJ(&obj)->height = BRICK_HEIGHT;
            GAMEOBJ(&obj)->color = color;
            obj.is_active = 1;
            obj.hit_count = brick_hit_count_table[color];
           
            this->bricks[this->active_brick_count++] = obj;
            start_x += (BRICK_WIDTH + ADJ);
        }
      
        start_x = 0;
        start_y += (BRICK_HEIGHT + ADJ);
    }
}

static void update(game_level* this) {
    if (this->active_brick_count == 0) {
        return;
    }

    this->active_brick_count--;
}

static void draw(const game_level* this) {
    int i;
    for (i = 0; i < BRICK_COUNT; ++i) {
        const brick* brick = &this->bricks[i];

        if (!brick->is_active) {
            continue;
        }
      
        rnd_draw_rect(
            GAMEOBJ(brick)->position.x, 
            GAMEOBJ(brick)->position.y, 
            GAMEOBJ(brick)->width, 
            GAMEOBJ(brick)->height, 
            GAMEOBJ(brick)->color);
    }
}

static int is_finished(const game_level* this) {
    return this->active_brick_count == 0;
}

static brick* get_brick(game_level* this, int index) {
    if (index < 0 || index >= BRICK_COUNT) {
        return NULL;
    }
    
    return &this->bricks[index];
}