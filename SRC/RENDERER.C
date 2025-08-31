#include "renderer.h"
#include "vga.h"

void rndPutchar(int x, int y, char color, const int (*font)[5][5]) {
    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if ((*font)[j][i]) {
                vgaPutPixel(x + i, y + j, color);
            }
        }
    }
}

void rndDrawRect(int x, int y, int width, int height, char color) {
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            vgaPutPixel(x + i, y + j, color);
        }
    }
}
