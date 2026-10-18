#include "ui.h"
#include <stdlib.h>
#include <string.h>
#include "fonts.h"
#include "renderer.h"
#include "gameobj.h"

#define SCORE_X 12
#define SCORE_Y 10
#define SCORE_ADJ 35
#define LIFE_X 200
#define LIFE_Y 10
#define LIFE_ADJ 30
#define ADJ 6

typedef struct {
    game_object base;
    
    union {
        int num;
        const char* str;
    } val;
} ui_element;

static ui_element score_text;
static ui_element score_num;
static ui_element life_text;
static ui_element life_num;
static ui_element game_over_text;

static void draw_text(const char* s, int x, int y, char color);
static void draw_number(int num, int x, int y, char color);

void init_ui(void) {
    GAMEOBJ(&score_text)->position.x = SCORE_X;
    GAMEOBJ(&score_text)->position.y = SCORE_Y;
    GAMEOBJ(&score_text)->color = 0xF;
    score_text.val.str = "SCORE:";
    
    GAMEOBJ(&score_num)->position.x = SCORE_X + SCORE_ADJ;
    GAMEOBJ(&score_num)->position.y = SCORE_Y;
    GAMEOBJ(&score_num)->color = 0xF;
    score_num.val.num = 0;

    GAMEOBJ(&life_text)->position.x = LIFE_X;
    GAMEOBJ(&life_text)->position.y = LIFE_Y;
    GAMEOBJ(&life_text)->color = 0xF;
    life_text.val.str = "LIFE:";
   
    GAMEOBJ(&life_num)->position.x = LIFE_X + LIFE_ADJ;
    GAMEOBJ(&life_num)->position.y = LIFE_Y;
    GAMEOBJ(&life_num)->color = 0xF;
    life_num.val.num = 0;
   
    GAMEOBJ(&game_over_text)->position.x = 130; 
    GAMEOBJ(&game_over_text)->position.y = 130;
    GAMEOBJ(&game_over_text)->color = 0xF;
    game_over_text.val.str = "GAME OVER";
}

void ui_update(int score, int life) {
    score_num.val.num = score;
    life_num.val.num = life;
}

void ui_draw(int is_game_over) {
    draw_text(score_text.val.str, 
        GAMEOBJ(&score_text)->position.x, 
        GAMEOBJ(&score_text)->position.y, 
        GAMEOBJ(&score_text)->color);
    
    draw_number(score_num.val.num, 
        GAMEOBJ(&score_num)->position.x, 
        GAMEOBJ(&score_num)->position.y, 
        GAMEOBJ(&score_num)->color);
    
    draw_text(life_text.val.str, 
        GAMEOBJ(&life_text)->position.x, 
        GAMEOBJ(&life_text)->position.y, 
        GAMEOBJ(&life_text)->color);

    draw_number(life_num.val.num, 
        GAMEOBJ(&life_num)->position.x, 
        GAMEOBJ(&life_num)->position.y, 
        GAMEOBJ(&life_num)->color);

    if (is_game_over) {
        draw_text(game_over_text.val.str, 
            GAMEOBJ(&game_over_text)->position.x, 
            GAMEOBJ(&game_over_text)->position.y, 
            GAMEOBJ(&game_over_text)->color);
    }
}

static void draw_text(const char* s, int x, int y, char color) {
    int i;
    for (i = 0; s[i] != '\0'; ++i) {
        rnd_put_char(x, y, color, ascii_font_table[(int)s[i]]);
        x += ADJ;
    }
}

static void draw_number(int num, int x, int y, char color) {
    char strNum[6];

    itoa(num, strNum, 10);
        
    draw_text(strNum, x, y, color);
}
