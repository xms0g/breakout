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

static ball ball;
static paddle paddle;
static level_mng level_mng;
static game_level* current_level;
static int is_running;
static int done;
static int score;
static int life;
static int is_game_over;

static const int brick_score_table[16] = {0,0,10,0,30,0,40,0,0,0,0,0,20,0,10,0};

static void do_collision(void);
static void reset_ball(void);

static void process_input(void) {
    if (kb_hit(ESC)) {
        is_running = 0;
    } else if (kb_hit(L_ARROW)) {
        paddle.move(&paddle, LEFT);
    } else if (kb_hit(R_ARROW)) {
        paddle.move(&paddle, RIGHT);
    }
}

static void update(void) {
    ui_update(score, life);

    ball.move(&ball);

    do_collision();
}

static void render(void) {
    vga_clr_offscreen(0x0);
    
    ball.draw(&ball);
    
    paddle.draw(&paddle);

    current_level = level_mng.get_current_level(&level_mng);
    current_level->draw(current_level);

    ui_draw(is_game_over);

    vga_update_vram();
}

static void do_collision(void) {
     if (GAMEOBJ(&ball)->position.y + GAMEOBJ(&ball)->height >= SCREEN_HEIGHT) {
        reset_ball();
        
        life--;
        
        if (life == 0) {
            done = 1;
            is_game_over = 1;
            ui_update(score, life);
        }
    } else if (check_aabb(GAMEOBJ(&ball), GAMEOBJ(&paddle))) {
        //determine where on the paddle we made a collision
        float ball_position =
            (GAMEOBJ(&paddle)->position.x + (GAMEOBJ(&paddle)->width >> 1)) - (GAMEOBJ(&ball)->position.x + (GAMEOBJ(&ball)->width >> 1));

        //bounce the ball off at an angle from 0 to 60 degrees
        //based on how close we are to the edges of the paddle
        float degrees = 60.0f * (ball_position / (float)(GAMEOBJ(&paddle)->width >> 1));
        float radians = degrees * (PI / 180.0f);

        //calculate the new ball speeds based on that angle
        float ball_x_move = BALL_SPEED * sin(radians)*-1;
        float ball_y_move = BALL_SPEED * cos(radians)*-1;
        ball.velocity.x = ball_x_move;
        ball.velocity.y = ball_y_move;
    } else {
        int i;
        current_level = level_mng.get_current_level(&level_mng);
    
        for (i = 0; i < BRICK_COUNT; ++i) {
            brick* brick = current_level->get_brick(current_level, i);
            
            if (!brick->isActive) continue;

            if (check_aabb(GAMEOBJ(&ball), GAMEOBJ(brick))) {
                brick->hitCount--;
                    
                if (brick->hitCount == 0) {
                    brick->isActive = 0;
                    
                    score += brick_score_table[GAMEOBJ(brick)->color];
                    
                    current_level->update(current_level);
                    
                    if (current_level->is_finished(current_level)) {
                        level_mng.load_next_level(&level_mng);
                        reset_ball();                       
                        break;
                    }
                }
                    
                ball.velocity.y = -ball.velocity.y;
                break;
            }
        }
    }
}

static void reset_ball(void) {
    ball.reset(
        &ball, 
        GAMEOBJ(&paddle)->position.x + (GAMEOBJ(&paddle)->width >> 1), 
        GAMEOBJ(&paddle)->position.y - BALL_RESET_OFFSET_Y);
}

static void init(void) {
    init_paddle(&paddle);
    paddle.new(&paddle, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 10, 0x5);

    init_ball(&ball);
    ball.new(
        &ball, 
        GAMEOBJ(&paddle)->position.x + (GAMEOBJ(&paddle)->width >> 1),
        GAMEOBJ(&paddle)->position.y - BALL_RESET_OFFSET_Y, 
        0xF);

    init_level_mng(&level_mng);
    level_mng.new(&level_mng);

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