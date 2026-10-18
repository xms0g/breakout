#ifndef LVLMNGR_H
#define LVLMNGR_H

#include "gamelvl.h"

typedef struct level_mng {
    game_level levels[4];
    int current_level_index;

    void (*new)(struct level_mng*);
    game_level* (*get_current_level)(struct level_mng*);
    void (*load_next_level)(struct level_mng*);
} level_mng;

void init_level_mng(level_mng* this);

#endif