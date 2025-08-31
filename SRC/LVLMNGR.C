#include "lvlmngr.h"
#include "renderer.h"
#include "levels.h"

static void lmNew(LevelManager* this);
static GameLevel* lmGetCurrentLevel(LevelManager* this);
static void lmLoadNextLevel(LevelManager* this);

void lmInit(LevelManager* this) {
    this->new = lmNew;
    this->getCurrentLevel = lmGetCurrentLevel;
    this->loadNextLevel = lmLoadNextLevel;

    this->currentLevelIndex = 0;
}

static void lmNew(LevelManager* this) {
    GameLevel one, two, three, four;
    
    glInit(&one);
    one.new(&one, levelOne);
    this->levels[0] = one;

    glInit(&two);
    two.new(&two, levelTwo);
    this->levels[1] = two;

    glInit(&three);
    three.new(&three, levelThree);
    this->levels[2] = three;

    glInit(&four);
    four.new(&four, levelFour);
    this->levels[3] = four;
    
    this->currentLevelIndex = 0;
}

static GameLevel* lmGetCurrentLevel(LevelManager* this) {
    return &this->levels[this->currentLevelIndex];
}

static void lmLoadNextLevel(LevelManager* this) {
    ++this->currentLevelIndex;

    if (this->currentLevelIndex > 3) {
        this->currentLevelIndex = 0;
    }
}