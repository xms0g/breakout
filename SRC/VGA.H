#ifndef VGA_H
#define VGA_H

enum colors {
    BLACK,		    /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,		/* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

void vga_init(void);

void vga_exit(void);
  
void vga_put_pixel(int x, int y, char color);

void vga_clr_offscreen(char color);

void vga_update_vram(void);

#endif