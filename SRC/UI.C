#include "UI.H"
#include <stdlib.h>
#include <string.h>
#include "FONTS.H"
#include "RENDERER.H"
#include "GAMEOBJ.H"

#define SCORE_X 12
#define SCORE_Y 10
#define SCORE_ADJ 35
#define LIFE_X 200
#define LIFE_Y 10
#define LIFE_ADJ 30
#define ADJ 6

typedef struct {
    GameObject base;
    
    union {
        int num;
        const char* str;
    } val;
} UIElement;

static UIElement scoreText;
static UIElement scoreNum;
static UIElement lifeText;
static UIElement lifeNum;
static UIElement gameOverText;

static void drawText(const char* s, int x, int y, char color);
static void drawNumber(int num, int x, int y, char color);

void uiInit(void) {
    GAMEOBJ(&scoreText)->position.x = SCORE_X;
    GAMEOBJ(&scoreText)->position.y = SCORE_Y;
    GAMEOBJ(&scoreText)->color = 0xF;
    scoreText.val.str = "SCORE:";
    
    GAMEOBJ(&scoreNum)->position.x = SCORE_X + SCORE_ADJ;
    GAMEOBJ(&scoreNum)->position.y = SCORE_Y;
    GAMEOBJ(&scoreNum)->color = 0xF;
    scoreNum.val.num = 0;

    GAMEOBJ(&lifeText)->position.x = LIFE_X;
    GAMEOBJ(&lifeText)->position.y = LIFE_Y;
    GAMEOBJ(&lifeText)->color = 0xF;
    lifeText.val.str = "LIFE:";
   
    GAMEOBJ(&lifeNum)->position.x = LIFE_X + LIFE_ADJ;
    GAMEOBJ(&lifeNum)->position.y = LIFE_Y;
    GAMEOBJ(&lifeNum)->color = 0xF;
    lifeNum.val.num = 0;
   
    GAMEOBJ(&gameOverText)->position.x = 130; 
    GAMEOBJ(&gameOverText)->position.y = 130;
    GAMEOBJ(&gameOverText)->color = 0xF;
    gameOverText.val.str = "GAME OVER";
}

void uiUpdate(int score, int life) {
    scoreNum.val.num = score;
    lifeNum.val.num = life;
}

void uiDraw(int isGameOver) {
    drawText(scoreText.val.str, 
        GAMEOBJ(&scoreText)->position.x, 
        GAMEOBJ(&scoreText)->position.y, 
        GAMEOBJ(&scoreText)->color);
    
    drawNumber(scoreNum.val.num, 
        GAMEOBJ(&scoreNum)->position.x, 
        GAMEOBJ(&scoreNum)->position.y, 
        GAMEOBJ(&scoreNum)->color);
    
    drawText(lifeText.val.str, 
        GAMEOBJ(&lifeText)->position.x, 
        GAMEOBJ(&lifeText)->position.y, 
        GAMEOBJ(&lifeText)->color);

    drawNumber(lifeNum.val.num, 
        GAMEOBJ(&lifeNum)->position.x, 
        GAMEOBJ(&lifeNum)->position.y, 
        GAMEOBJ(&lifeNum)->color);

    if (isGameOver) {
        drawText(gameOverText.val.str, 
            GAMEOBJ(&gameOverText)->position.x, 
            GAMEOBJ(&gameOverText)->position.y, 
            GAMEOBJ(&gameOverText)->color);
    }
}

static void drawText(const char* s, int x, int y, char color) {
    int i;
    for (i = 0; i < s[i] != '\0'; ++i) {
        rndPutchar(x, y, color, asciiFontTable[(int)s[i]]);
        x += ADJ;
    }
}

static void drawNumber(int num, int x, int y, char color) {
    char strNum[6];

    itoa(num, strNum, 10);
        
    drawText(strNum, x, y, color);
}
