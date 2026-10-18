#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#define GAMEOBJ(ptr) ((game_object*)(ptr))

typedef struct game_object {
    struct {
        float x; 
        float y;
    } position;
    
    int width; 
    int height;
    char color;
} game_object;

typedef struct {
    float x;
    float y;
} velocity;

#endif