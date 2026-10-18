#include "lvlmngr.h"
#include "renderer.h"
#include "levels.h"

static void new(level_mng* this);
static game_level* get_current_level(level_mng* this);
static void load_next_level(level_mng* this);

void init_level_mng(level_mng* this) {
    this->new = new;
    this->get_current_level = get_current_level;
    this->load_next_level = load_next_level;

    this->current_level_index = 0;
}

static void new(level_mng* this) {
    game_level one, two, three, four;
    
    init_game_lvl(&one);
    one.new(&one, level_one);
    this->levels[0] = one;

    init_game_lvl(&two);
    two.new(&two, level_two);
    this->levels[1] = two;

    init_game_lvl(&three);
    three.new(&three, level_three);
    this->levels[2] = three;

    init_game_lvl(&four);
    four.new(&four, level_four);
    this->levels[3] = four;
    
    this->current_level_index = 0;
}

static game_level* get_current_level(level_mng* this) {
    return &this->levels[this->current_level_index];
}

static void load_next_level(level_mng* this) {
    ++this->current_level_index;

    if (this->current_level_index > 3) {
        this->current_level_index = 0;
    }
}