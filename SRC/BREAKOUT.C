#include <math.h>
#include <stdio.h>
#include "vga.h"
#include "keybrd.h"
#include "paddle.h"
#include "ball.h"
#include "renderer.h"
#include "conf.h"
#include "aabb.h"
#include "lvlmngr.h"
#include "ui.h"

#define PI 3.14159f

static ball this_ball;
static paddle this_paddle;
static level_mng lvl_mng;
static game_level* current_level;
static int is_running;
static int done;
static int score;
static int life;
static int is_game_over;

static const int brick_score_table[16] = {0,0,10,0,30,0,40,0,0,0,0,0,20,0,10,0};

static void do_collision(void);
static void reset(void);

static void process_input(void) {
    if (kb_hit(ESC)) {
        is_running = 0;
    } else if (kb_hit(L_ARROW)) {
        this_paddle.move(&this_paddle, LEFT);
    } else if (kb_hit(R_ARROW)) {
        this_paddle.move(&this_paddle, RIGHT);
    }
}

static void update(void) {
    ui_update(score, life);

    this_ball.move(&this_ball);

    do_collision();
}

static void render(void) {
    vga_clr_offscreen(0x0);
    
    this_ball.draw(&this_ball);
    this_paddle.draw(&this_paddle);

    current_level = lvl_mng.get_current_level(&lvl_mng);
    current_level->draw(current_level);

    ui_draw(is_game_over);

    vga_update_vram();
}

static void do_collision(void) {
     if (GAMEOBJ(&this_ball)->position.y + GAMEOBJ(&this_ball)->height >= SCREEN_HEIGHT) {
        reset();
        
        life--;
        
        if (life == 0) {
            done = 1;
            is_game_over = 1;
            ui_update(score, life);
        }
    } else if (check_aabb(GAMEOBJ(&this_ball), GAMEOBJ(&this_paddle))) {
        //determine where on the this_paddle we made a collision
        float ball_position =
            (GAMEOBJ(&this_paddle)->position.x + (GAMEOBJ(&this_paddle)->width >> 1)) - (GAMEOBJ(&this_ball)->position.x + (GAMEOBJ(&this_ball)->width >> 1));

        //bounce the this_ball off at an angle from 0 to 60 degrees
        //based on how close we are to the edges of the this_paddle
        float degrees = 60.0f * (ball_position / (float)(GAMEOBJ(&this_paddle)->width >> 1));
        float radians = degrees * (PI / 180.0f);

        //calculate the new this_ball speeds based on that angle
        float ball_x_move = BALL_SPEED * sin(radians)*-1;
        float ball_y_move = BALL_SPEED * cos(radians)*-1;
        this_ball.velocity.x = ball_x_move;
        this_ball.velocity.y = ball_y_move;
    } else {
        int i;
        current_level = lvl_mng.get_current_level(&lvl_mng);
    
        for (i = 0; i < BRICK_COUNT; ++i) {
            brick* brick = current_level->get_brick(current_level, i);
            
            if (!brick->is_active) continue;

            if (check_aabb(GAMEOBJ(&this_ball), GAMEOBJ(brick))) {
                brick->hit_count--;
                    
                if (brick->hit_count == 0) {
                    brick->is_active = 0;
                    
                    score += brick_score_table[GAMEOBJ(brick)->color];
                    
                    current_level->update(current_level);
                    
                    if (current_level->is_finished(current_level)) {
                        lvl_mng.load_next_level(&lvl_mng);
                        reset();                       
                        break;
                    }
                }
                    
                this_ball.velocity.y = -this_ball.velocity.y;
                break;
            }
        }
    }
}

static void reset(void) {
    this_ball.reset(
        &this_ball, 
        GAMEOBJ(&this_paddle)->position.x + (GAMEOBJ(&this_paddle)->width >> 1), 
        GAMEOBJ(&this_paddle)->position.y - BALL_RESET_OFFSET_Y);
}

static void init(void) {
    init_paddle(&this_paddle);
    this_paddle.new(&this_paddle, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 10, 0x5);

    init_ball(&this_ball);
    this_ball.new(
        &this_ball, 
        GAMEOBJ(&this_paddle)->position.x + (GAMEOBJ(&this_paddle)->width >> 1),
        GAMEOBJ(&this_paddle)->position.y - BALL_RESET_OFFSET_Y, 
        0xF);

    init_level_mng(&lvl_mng);
    lvl_mng.new(&lvl_mng);

    vga_init();
    init_ui();
    kb_init();

    score = done = is_game_over = 0;

    life = PLAYER_LIFE;

    is_running = 1;
}

void main(void) {
    init();
    
    while (is_running) {
        process_input();
        
        if (!done) {
            update();
            render();
        }
    }

    vga_exit();
    kb_exit();
    
    printf("%s", "\tDeveloped by M. Sami GURPINAR\n     In a lot of blood, sweat, and tears.\n");
}