#ifndef AABB_H
#define AABB_H

struct game_object;
int check_aabb(const struct game_object* one, const struct game_object* two);

#endif