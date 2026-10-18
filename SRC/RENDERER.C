#include "renderer.h"
#include "vga.h"

void rnd_put_char(int x, int y, char color, const int (*font)[5][5]) {
    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if ((*font)[j][i]) {
                vga_put_pixel(x + i, y + j, color);
            }
        }
    }
}

void rnd_draw_rect(int x, int y, int width, int height, char color) {
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            vga_put_pixel(x + i, y + j, color);
        }
    }
}
