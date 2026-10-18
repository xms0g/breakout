#ifndef RENDERER_H
#define RENDERER_H

void rnd_put_char(int x, int y, char color, const int (*font)[5][5]);

void rnd_draw_rect(int x, int y, int width, int height, char color);

#endif